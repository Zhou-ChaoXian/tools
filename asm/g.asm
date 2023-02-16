assume cs:code

code segment
    start:
        call show_str
        mov ax,4c00h
        int 21h

    ;在屏幕上显示输入的字符串，退格键删除，esc停止，tab设置颜色
    show_str:
        push ax
        push bx
        push cx
        push es
        push di
        push dx

        mov ax,0b800h
        mov es,ax
        mov di,0
        mov dx,0
        ;光标放在开头
        call set_pointer
        ;颜色信息 0-7
        mov cx,0
    
    show_str_again:
        mov ah,0
        int 16h

        ;esc，结束
        cmp al,1bh
        je show_str_end
        ;退格键，删除一个
        cmp al,8
        je show_str_fn1
        ;enter，换行
        cmp al,0dh
        je show_str_fn2
        ;tab，设置颜色
        cmp al,9
        je show_str_fn3
        ;大于空格都显示
        cmp al,' '
        jae show_str_fn
        jmp short show_str_again
    
    ;显示一个新字符
    show_str_fn:
        mov es:[di],al
        add di,2
        ;列号加1
        inc dl
        mov bx,0
        call set_pointer
        jmp short show_str_again
    ;删除最后一个字符
    show_str_fn1:
        cmp di,0
        je show_str_again
        sub di,2
        ;列号等于0，列号直接等于79
        cmp dl,0
        jz show_str_set_new_col
        dec dl
        jmp short show_str_set_pointer
    show_str_set_new_col:
        dec dh
        mov dl,79
    show_str_set_pointer:
        mov bx,1
        call set_pointer
        mov byte ptr es:[di],' '
        jmp short show_str_again
    ;设置字体颜色
    show_str_fn3:
        mov al,cl
        call set_color
        inc cl
        cmp cl,7
        jbe show_str_again
        mov cl,0
        jmp short show_str_again
        
    ;处理enter，直接换行
    show_str_fn2:
        mov ah,dh
        inc ah
        mov al,160
        mul ah
        mov di,ax
        call set_pointer
        jmp short show_str_again

    show_str_end:
        pop dx
        pop di
        pop es
        pop cx
        pop bx
        pop ax
        ret

    ;设置光标的位置，int10h中断例程2号子程序
    ;dx存储行号和列号
    set_pointer:
        call set_dx
        push ax
        push bx
        mov ah,2
        mov bh,0
        int 10h
        pop bx
        pop ax
        ret
    
    ;根据di设置dx，如果di是160的倍数，dh加1，dl等于0
    set_dx:
        push ax
        push bx
        cmp di,0
        je set_dx_end
        test bx,1
        jnz set_dx_end
        mov ax,di
        mov bl,160
        div bl
        cmp ah,0
        jne set_dx_end
        inc dh
        and dl,0
    set_dx_end:
        pop bx
        pop ax
        ret

    ;设置字体颜色
    ;al存储颜色信息 1-7
    set_color:
        push ax
        push es
        push di
        push cx

        push ax
        mov ax,0b800h
        mov es,ax
        mov di,1
        mov cx,2000
        pop ax
    set_color_next:
        and byte ptr es:[di],0f8h
        or es:[di],al
        add di,2
        loop set_color_next

        pop cx
        pop di
        pop es
        pop ax
        ret
code ends
end start