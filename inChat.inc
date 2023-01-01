inititializeChat proc
pusha
    mov chatModeMeCursorY,05h
    mov chatModeYouCursorY,09h
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