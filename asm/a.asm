assume cs:code

data segment
    db 16 dup (0)
    dw 123,1,8,2559,567
data ends

code segment
    start:
        mov ax,data
        mov ds,ax
        mov si,0
        mov bx,16
        mov di,0

        mov cx,5

        _s:
            mov ax,[bx+di]
            call dtoc

            mov ax,di

            push cx
            mov cx,8
            shl ax,cl
            pop cx
            add ax,501h
            mov dx,ax
            push cx
            mov cl,24h
            call show_str
            pop cx
            add di,2
            loop _s

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
            jcxz over
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

    ;字形数据转换成字符串
    ;ax word数据
    ;ds:si字符串首地址
    dtoc:
        push ax
        push bx
        push cx
        push dx
        push si

        mov cx,0
        mov bx,0  ;计数用
        mov dl,10

        ;除以10取余
        s0:
            div dl
            add ah,30h
            mov [si],ah
            inc si
            inc bx
            ;重新设置ax为商
            mov cl,al
            jcxz over1
            mov ax,cx
            jmp short s0

        over1:
            ;设置最后一位为0
            mov byte ptr [si],0
            mov si,0
            ;保存位数
            push bx
            mov ax,bx
            mov bl,2
            div bl
            ;循环次数
            mov cl,al
            mov ch,0
            ;总位数
            pop bx
            jcxz ok
            dec bx

            s1:
                push bx
                mov al,[si]
                sub bx,si
                mov ah,[bx]
                mov [si],ah
                mov [bx],al
                pop bx
                inc si
                loop s1
            ok:
                nop
            pop si
            pop dx
            pop cx
            pop bx
            pop ax
            ret

code ends
end start