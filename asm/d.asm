assume cs:code,ds:data

data segment
    db 'hello world','$'
    db 'hi beautiful girl!',0
data ends

code segment
    start:
        mov dx,511h
        call set_pointer

        mov al,'a'
        mov bl,24h
        mov cx,8
        call rep_str

        mov dx,611h
        call set_pointer

        mov ax,data
        mov ds,ax
        mov dx,0
        call show_str

        call install_project
        mov ax,data
        mov ds,ax
        mov si,12
        mov dx,211h
        mov cl,42h
        int 7ch
        
        mov ax,4c00h
        int 21h

    ;设置光标位置
    ;dh行号 dl列号
    set_pointer:
        push ax
        push bx
        mov ah,2
        mov bh,0
        int 10h
        pop bx
        pop ax
        ret
    
    ;重复显示字符
    ;al字符  bl颜色  cx显示次数
    rep_str:
        push ax
        push bx
        push cx
        mov ah,9
        mov bh,0
        mov cx,3
        int 10h
        pop cx
        pop bx
        pop ax
        ret

    ;显示以$结尾的字符串
    ;ds:dx 指向字符串
    show_str:
        push ax
        mov ah,9
        int 21h
        pop ax
        ret
    
    ;安装7ch中断例程
    install_project:
        push ax
        push ds
        push es
        push si
        push di
        push cx

        mov ax,cs
        mov ds,ax
        mov si,offset show_str_plus

        mov ax,0
        mov es,ax
        mov di,200

        mov cx,offset show_str_plus_end - offset show_str_plus
        cld
        rep movsb
        
        mov word ptr es:[7ch*4],200
        mov word ptr es:[7ch*4+2],0

        pop cx
        pop di
        pop si
        pop es
        pop dx
        pop ax
        ret
        

    ;显示以0结尾的字符串，int 7ch中断例程
    ;dh行号  dl列号  cl颜色  ds:si指向字符串
    show_str_plus:
        push ax
        push es
        push si
        push di

        mov ax,0b800h
        mov es,ax
        
        ;根据行号列号计算位置
        mov al,160
        mul dh
        push ax
        mov al,2
        mul dl
        pop di
        add di,ax

    show_str_plus_next:
        mov al,[si]
        cmp al,0
        je show_str_plus_over
        mov byte ptr es:[di],al
        mov byte ptr es:[di+1],cl
        inc si
        add di,2
        jmp short show_str_plus_next

    show_str_plus_over:
        pop di
        pop si
        pop es
        pop ax
        iret
    show_str_plus_end:
        nop

code ends
end start