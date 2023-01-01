startMainMenu PROC NEAR
       MOV BH, 0

       ;move cursor to 25,09
       mov ah,2
       mov bh,0
       mov dl,25
       mov dh,09
       int 10h

       MOV AH, 09H
       MOV DX, OFFSET chatting_mode
       INT 21H

       ;move cursor to 25,11
       mov ah,2
       mov bh,0
       mov dl,25
       mov dh,11
       int 10h

       MOV AH, 09H
       MOV DX, OFFSET game_mode
       INT 21H

       ;move cursor to 25,12
       mov ah,2
       mov bh,0
       mov dl,25
       mov dh,13
       int 10h

       MOV AH, 09H
       MOV DX, OFFSET end_game
       INT 21H

       MOV AH, 02
       MOV BH, 0
       MOV DH, 20
       MOV DL, 0
       INT 10H

       MOV AH, 09H
       MOV DX, OFFSET rr
       INT 21H

       RET
startMainMenu ENDP

handleNotificationSection macro Option
    LOCAL emptyMessageSection, welcomeOption,sentGameRequestOption,sentChatRequestOption,gotChatRequestOption,gotGameRequestOption,END
    pusha

    mov dh,21
    mov cx,4
    emptyMessageSection: ;21 to 24
        mov ah, 02
        mov bh, 0
        mov dh, 21
        mov dl, 0
        int 10H
        
        mov ah, 09H
        printMsg emptyHorizontalLine
        inc dh
        loop emptyMessageSection


    mov dh, 21

    cmp Option, 1
    jne welcomeOption
    
    mov ah, 02
    mov dl, 0
    int 10H

    mov ah, 09H
    printMsg waiting_msg
    inc dh
    
    welcomeOption:
    cmp Option, 2
    jne sentChatRequestOption
    mov ah, 02
    mov dl, 0
    int 10H
    
    mov ah, 09H
    printMsg connected_msg
    printMsg secondPlayerName
    inc dh

    sentChatRequestOption:
    cmp Option, 3
    jne sentGameRequestOption
    mov ah, 02
    mov dl, 0
    int 10H

    printMsg sentChatRequestMsg
    printMsg secondPlayerName
    inc dh

    sentGameRequestOption:
    cmp Option, 4
    jne gotChatRequestOption
    mov ah, 02
    mov dl, 0
    int 10H

    printMsg sentGameRequestMsg
    printMsg secondPlayerName
    inc dh
    
    gotChatRequestOption:
    cmp Option, 5
    jne gotGameRequestOption
    mov ah, 02
    mov dl, 0
    int 10H

    printMsg gotChatRequestMsg
    printMsg secondPlayerName
    inc dh
    
    gotGameRequestOption:
    cmp Option, 6
    jne END
    mov ah, 02
    mov dl, 0
    int 10H

    printMsg gotGameRequestMsg
    printMsg secondPlayerName
    inc dh

    END:
    popa
ENDM handleNotificationSection