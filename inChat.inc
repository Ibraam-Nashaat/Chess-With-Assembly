scrollInLineUpperPart proc 
    push ax

    mov ah, 6
    mov al, 1
    mov bh, 7

    mov ch, 06h
    mov cl, 19h

    mov dh, 0ch
    mov dl, 39
    int 10h

    call getCursorPosition
    mov al, 12
    mov pos+1, al
    call setCursorPosition

    pop ax
    ret
scrollInLineUpperPart ENDP 

scrollInLineLowerPart proc 
    push ax
    
    mov ah, 6
    mov al, 1
    mov bh, 0
    
    mov ch, 0fh
    mov cl, 19h

    mov dh, 17h
    mov dl, 39
    int 10h

    call getCursorPosition

    mov al, 22
    mov pos+1, al
    call setCursorPosition

    pop ax
    ret
scrollInLineLowerPart ENDP 

inititializeChat proc
pusha
    mov chatModeMeCursorY,06h ; (06->0c)
    mov chatModeYouCursorY,0fh; (0f-> 17)
    mov chatModeMeCursorX,19h
    mov chatModeYouCursorX,19h

    mov pos,19h
    mov pos+1,0dh
    call setCursorPosition
    printMsg rrInlineChat

    mov pos,19h
    mov pos+1,0eh
    call setCursorPosition
    printMsg str1

    mov pos,19h
    mov pos+1,05h
    call setCursorPosition
    printMsg str2


popa
ret
inititializeChat endp

printReceivedChar proc
pusha
        mov bh,chatModeYouCursorX
        mov pos,bh
        mov bh,chatModeYouCursorY
        mov pos+1,bh
        call setCursorPosition

        cmp VALUE,13
        je return17


        @print_character1:
            checkInLineChatModeYouY:
                cmp chatModeYouCursorY, 18h
                jl printYouInLineChar

            scrollYouInLinePart:
                call scrollInLineLowerPart

            printYouInLineChar:
            printCharacter VALUE
            call getCursorPosition
            mov bh,pos
            cmp bh,0
            je resetYouCursorPosX
        setYouCursorY:    mov chatModeYouCursorX,bh
                         mov bh,pos+1
                         mov chatModeYouCursorY,bh
                         jmp return17

        resetYouCursorPosX:mov bh,19h
                       jmp setYouCursorY

    return17:
popa
ret
printReceivedChar endp

printTransmitterChar proc
pusha
        mov bh,chatModeMeCursorX
        mov pos,bh
        mov bh,chatModeMeCursorY
        mov pos+1,bh
        call setCursorPosition

        cmp VALUE,13
        je return18


        @print_character2:
            printCharacter VALUE
            mov al,VALUE
            mov dataToSend+4,al
            call getCursorPosition
            mov bh,pos
            cmp bh,0
            je resetMeCursorPosX
        setMeCursorY:    mov chatModeMeCursorX,bh
                         mov bh,pos+1
                         mov chatModeMeCursorY,bh
                         jmp return18

        resetMeCursorPosX:mov bh,19h
                       jmp setMeCursorY

    return18:
popa
ret

printTransmitterChar endp