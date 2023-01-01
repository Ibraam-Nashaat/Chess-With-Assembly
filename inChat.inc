inititializeChat proc
pusha
    mov chatModeMeCursorY,05h
    mov chatModeYouCursorY,0eh
    mov chatModeMeCursorX,1Ch
    mov chatModeYouCursorX,1dh

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