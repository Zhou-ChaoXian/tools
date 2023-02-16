assume cs:code

code segment
    start:  mov ax,cs
            mov ds,ax
            mov si,offset do0
            mov ax,0
            mov es,ax
            mov di,200h
            mov cx,offset do0end-offset do0
            cld
            rep movsb

            mov word ptr es:[0],200h     ;0号中断
            mov word ptr es:[2],0

            mov ax,1000h
            mov bl,1
            div bl

            mov ax,4c00h
            int 21h 
    do0:    jmp short do0start
            db 'divide error!',0
    do0start:   mov ax,cs
                mov ds,ax
                mov si,202h
                mov ax,0b800h
                mov es,ax
                mov di,12*160+30*2
                mov ah,0c2h
                mov cx,0
    s:          mov cl,[si]
                jcxz over
                mov al,cl
                mov es:[di],ax
                inc si
                add di,2
                jmp short s
    over:        mov ax,4c00h
                int 21h
    do0end: nop
code ends
end start