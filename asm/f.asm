assume cs:code

code segment
    start:
        mov ah,24h
        mov dx,511h
        mov al,30
        call show_sin

        mov ax,4c00h
        int 21h
    
    ;显示sin的结果
    ;al存储sin的度数
    ;ah存储颜色信息
    ;dx行号列号
    show_sin:
        call check_sin
        jmp short show_sin_begin
        ;直接定址表
        show_sin_table dw show_sin_0,show_sin_30,show_sin_60,show_sin_90,show_sin_120,show_sin_150,show_sin_180
        show_sin_0 db '0',0
        show_sin_30 db '0.5',0
        show_sin_60 db '0.866',0
        show_sin_90 db '1',0
        show_sin_120 db '0.866',0
        show_sin_150 db '0.5',0
        show_sin_180 db '0',0
    show_sin_begin:
        push ax
        push bx
        push es
        push di
        push ds
        push si

        ;保存颜色信息
        push ax
        ;度数除以30取商，2倍，得到偏移地址bx
        mov ah,0
        mov bl,30
        div bl
        mov bl,al
        mov bh,0
        add bx,bx
        mov bx,show_sin_table[bx]

        ;在屏幕中间显示结果
        mov ax,cs
        mov ds,ax
        mov si,bx
        ;恢复颜色信息
        pop ax
        call show_str
    
    show_sin_end:
        pop si
        pop ds
        pop di
        pop es
        pop bx
        pop ax
        ret
    
    ;检查度数，0-180之间，而且是30的倍数
    ;度数在al中
    check_sin:
        jmp short check_sin_begin
        check_sin_fail_msg db 'check fail',0

    check_sin_begin:
        push ax
        push bx
        ;这里一定注意，ja jb是无符号数比较，jl jg是有符号数比较，用无符号数比较
        cmp al,0
        jb check_sin_fail
        cmp al,180
        ja check_sin_fail
        mov ah,0
        mov bl,30
        div bl
        cmp ah,0
        jnz check_sin_fail
        pop bx
        pop ax
        ret
    
    ;检查失败退出
    check_sin_fail:
        mov ax,cs
        mov ds,ax
        lea si,check_sin_fail_msg
        mov dx,511h
        mov ah,4
        call show_str
        mov ax,4c00h
        int 21h

    
    ;显示字符串
    ;ds:si指向字符串
    ;dx行号和列号
    ;ah存储颜色
    show_str:
        push ax
        push es
        push di
        push si

        push ax
        ;es:di指向显示位置
        mov ax,0b800h
        mov es,ax
        mov di,0
        mov al,160
        mul dh
        push ax
        mov al,2
        mul dl
        pop di
        add di,ax

        ;复制ds:si到es:di中，弹出ax,恢复颜色信息
        pop ax
        cld
    show_str_next:
        mov al,[si]
        cmp al,0
        je show_str_end
        stosw
        inc si
        jmp short show_str_next
    
    show_str_end:
        pop si
        pop di
        pop es
        pop ax
        ret

code ends
end start