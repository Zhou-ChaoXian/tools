assume cs:code,ss:stack

stack segment
    dw 16 dup (0)
stack ends

code segment
    start:
        mov ax,stack
        mov ss,ax
        mov sp,20h

        call install_div_overflow

        mov ax,1234h
        mov bl,3h
        div bl
        mov ax,4c00h
        int 21h
    
    ;安装除法溢出程序，除法溢出会调用int 0中断例程
    install_div_overflow:
        push ax
        push ds
        mov ax,0
        mov ds,ax
        mov word ptr ds:[0],offset div_error
        mov word ptr ds:[2],cs
        pop ds
        pop ax
        ret

    ;除法错误
    div_error:
        jmp short div_error_msg_over
        div_error_msg:
            db 'div error,overflow!',0
        div_error_msg_over:
            mov ax,cs
            mov ds,ax
            mov si,offset div_error_msg
            mov dx,501h
            mov cl,1100b
            call show_str
            mov ax,4c00h
            int 21h
        
    ;dh 行号 1-25
    ;dl 列号 1-160
    ;cl 颜色
    ;ds:si 字符串地址
    show_str:
        push ax
        push bx
        push cx
        push es
        push si
        push di
        
        ;设置显存地址
        mov ax,0b800h
        mov es,ax
        mov di,0

        ;通过行号列号计算偏移量，存到bx中
        push dx
        mov al,160
        dec dh
        mul dh
        push ax
        mov al,2
        dec dl
        mul dl
        pop bx
        add bx,ax
        pop dx
        
        ;颜色信息
        mov al,cl
        mov ch,0

        ;循环，开始复制
        show_str_s:
            mov cl,[si]
            jcxz show_str_over
            mov es:[bx+di],cl
            mov es:[bx+di+1],al
            inc si
            add di,2
            jmp short show_str_s

        ;结束
        show_str_over:
            pop di
            pop si
            pop es
            pop cx
            pop bx
            pop ax
            ret
code ends
end start