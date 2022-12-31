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

handleMainActions PROC NEAR 
    ;press the key
    mov ah,0
    int 16h
    ;conditions
    ;F1
    mov bl,3Bh
    cmp ah,bl
    jz setChattingMode
    ;F2
    mov bl,3Ch
    cmp ah,bl
    jz setGameMode
    ;ESC
    mov bl,01
    cmp ah,bl
    jz setEsc

    mov cl,escEnc
    jmp continueToModeCheck

    setChattingMode:
        mov cl,chatModeEnc
        jmp continueToModeCheck

    setGameMode:
        mov cl,gameModeEnc
        jmp continueToModeCheck

    setEsc:
        mov cl,escEnc
        jmp continueToModeCheck
    
    continueToModeCheck:
    cmp cl,chatModeEnc
    je chatMode

    cmp cl,gameModeEnc
    je startGame

    jmp exit

    ;call the drawing module to draw the grid and pieces
    startGame :
        call initializeGame
        call initializeEatenArray
        mov al,0
        mov exitFlag,al
        ;Open the graphics mode
        mov ah,0
        mov al,13h
        int 10h
        call Draw
        call printEatenPieces

        infiniteLoop: 
            call moveArrow
            mov al,exitFlag
            cmp al,1d
            je waitPress
            jmp infiniteLoop

    waitPress:
        mov ah,0
        int 16h
        call handleMainActions

    chatMode:
        call startChatMode
    ret
handleMainActions endp

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