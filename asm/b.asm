assume cs:code,ds:data

data segment
    db '0123456789abcdef'
    db 16 dup (0)
    db "Beginner's All-purpose Symbolic Instruction Code.",0
data ends

code segment
    start:
        mov ax,data
        mov ds,ax
        mov es,ax
        mov si,0
        mov di,16

        mov cx,16
        cld
        rep movsb

        mov si,16
        mov dx,601h
        mov cl,42h
        call show_str

        mov si,32

        call uppercase

        mov si,32
        mov dx,501h
        mov cl,24h
        call show_str

        mov ax,4c00h
        int 21h
    
    ;ds:si字符串地址
    ;小写字母转换成大写字母
    uppercase:
        push ax
        push si

        uppercasestart:
            mov al,[si]
            cmp al,0
            jz uppercaseover
            cmp al,'a'
            jb uppercasenext
            cmp al,'z'
            ja uppercasenext
            and al,0dfh
            mov [si],al
        uppercasenext:
            inc si
            jmp short uppercasestart
        uppercaseover:
            pop si
            pop ax
            ret
    
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
        s:
            mov cl,[si]
            jcxz over
            mov es:[bx+di],cl
            mov es:[bx+di+1],al
            inc si
            add di,2
            jmp short s

        ;结束
        over:
            pop di
            pop si
            pop es
            pop cx
            pop bx
            pop ax
            ret
code ends
end start