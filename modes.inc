startMainMenu proc
       mov bh, 0

       ;move cursor to 25,09
       mov ah,2
       mov bh,0
       mov dl,25
       mov dh,09
       int 10h

       mov ah, 09H
       mov dx, OFFSET chatting_mode
       int 21h

       ;move cursor to 25,11
       mov ah,2
       mov bh,0
       mov dl,25
       mov dh,11
       int 10h

       mov ah, 09H
       mov dx, OFFSET game_mode
       int 21h

       ;move cursor to 25,12
       mov ah,2
       mov bh,0
       mov dl,25
       mov dh,13
       int 10h

       mov ah, 09H
       mov dx, OFFSET end_game
       int 21h

       mov ah, 02
       mov bh, 0
       mov dh, 20
       mov dl, 0
       int 10h

       mov ah, 09H
       mov dx, OFFSET rr
       int 21h

       RET
startMainMenu ENDP

handleNotificationSection macro Option
    LOCAL emptyMessageSection, welcomeOption, noConnectionMainMenuChoice
    pusha

    mov dh,21
    mov cx,4
    emptyMessageSection: ;21 to 24
        mov ah, 02
        mov bh, 0
        mov dh, 21
        mov dl, 0
        int 10h
        
        mov ah, 09H
        printMsg emptyHorizontalLine
        inc dh
        loop emptyMessageSection


    mov dh, 21

    cmp Option, 1
    jne welcomeOption
    
    mov ah, 02
    mov dl, 0
    int 10h

    mov ah, 09H
    printMsg waiting_msg
    inc dh
    
    welcomeOption:
    cmp Option, 2
    jne noConnectionMainMenuChoice
    mov ah, 02
    mov dl, 0
    int 10h
    
    printMsg connected_msg
    printMsg secondPlayerName

    noConnectionMainMenuChoice:
    popa
ENDM handleNotificationSection