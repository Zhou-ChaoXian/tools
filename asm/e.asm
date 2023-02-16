assume cs:code

code segment
    start:
        mov dx,500h
        mov di,24h
        call get_datetime
        mov ax,4c00h
        int 21h
    
    ;获取时间
    ;年9  月8  日7  时4  分2  秒0
    ;dx位置信息
    ;di低8位颜色信息
    get_datetime:
        jmp short get_datetime_start
    get_datetime_number:
        db 9,8,7,4,2,0
    get_datetime_str:
        db '// ::',0
    get_datetime_start:
        push ax
        push bx
        push cx
        push ds
        push dx
        push si

        mov ax,cs
        mov ds,ax
        mov bx,offset get_datetime_number
        mov si,offset get_datetime_str
        mov cx,6

        ;打印20
        push cx
        mov ax,3230h
        mov cx,di
        call show_datetime
        pop cx
        ;位置信息
        mov dx,502h
    get_datetime_next:
        mov al,[bx]
        call get_detail_info
        push cx
        mov cx,di
        mov ch,[si]
        call show_datetime
        ;dx加3，位置信息,3列
        add dx,3
        pop cx
        inc bx
        inc si
        loop get_datetime_next

        pop si
        pop dx
        pop ds
        pop cx
        pop bx
        pop ax
        ret
    
    ;显示日期信息
    ;ax存储日期信息 bcd码
    ;dx存储行号列号
    ;cl颜色信息
    ;ch存储数字末尾信息
    show_datetime:
        push ax
        push es
        push di
        push cx

        push ax
        ;es:di位置信息
        mov ax,0b800h
        mov es,ax
        mov al,160
        mul dh
        push ax
        mov al,2
        mul dl
        pop di
        add di,ax
        
        pop ax
        ;显示数据
        mov es:[di],ah
        mov es:[di+1],cl
        mov es:[di+2],al
        mov es:[di+3],cl
        cmp ch,0
        je show_datetime_no
        mov es:[di+4],ch
        mov es:[di+5],cl
    show_datetime_no:
        pop cx
        pop di
        pop es
        pop ax
        ret

    ;获取详细位置时间
    ;al存储位置
    ;结果存放在ax中
    get_detail_info:
        push cx
        out 70h,al
        in al,71h
        mov ah,al
        mov cl,4
        shr ah,cl
        add ah,30h
        and al,0fh
        add al,30h
        pop cx
        ret

code ends
end start