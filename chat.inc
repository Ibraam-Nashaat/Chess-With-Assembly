scrollUpperPart proc 
    push ax

    mov ah, 6
    mov al, 1
    mov bh, 7

    mov ch, 1 ;(1,0)
    mov cl, 0

    mov dh, 12;(12,79)
    mov dl, 79
    int 10h

    mov ah, 03
    mov bh, 0
    int 10h
    dec dh

    mov ah, 2
    int 10h
    pop ax
    ret
scrollUpperPart ENDP 

scrollLowerPart proc 
    push ax
    
    mov ah, 6
    mov al, 1
    mov bh, 7
    
    mov ch, 15 ;(15, 0)
    mov cl, 0

    mov dh, 22 ;(22, 79)
    mov dl, 79
    int 10h

    mov ah, 03
    mov bh, 0
    int 10h
    dec dh

    mov ah, 2
    int 10h
    pop ax
    ret
scrollLowerPart ENDP 

startChatMode proc
    ; clearing the screen
    mov ax,3
    int 10h

    mov chatModeMeCursorY,1
    mov chatModeYouCursorY,15
    mov pos,0
    mov pos+1,13
    call setCursorPosition

    printMsg rr
    printMsg firstPlayerName

    mov pos,0
    mov pos+1,0
    call setCursorPosition
    printMsg secondPlayerName

    mov tra_bool,0
    mov rec_bool,0

    mov chatModeMeCursorX, 0
    mov chatModeYouCursorX, 0

    chatOuterLoop:
    ;; check if we have to receive something
    call UART_rec
    cmp rec_bool,1
    jne continueToTransmit

    ;If Ready read the VALUE in Receive data register
    pusha
        mov dx , 03F8H
        in al , dx 
        mov VALUE , al
                
        mov rec_bool,0
        mov bh,chatModeYouCursorX
        mov pos,bh
        mov bh,chatModeYouCursorY
        mov pos+1,bh
        call setCursorPosition

        cmp VALUE,13
        jne print_character1
        inc pos+1
        mov pos,0
        call setCursorPosition

        mov chatModeYouCursorX,0
        mov bh,pos+1
        mov chatModeYouCursorY,bh
        jmp continueToTransmit

        print_character1:

            checkChatModeYouY:
            cmp chatModeYouCursorY, 23
            jl printYouChar

            scrollYouPart:
                call scrollLowerPart
            
            printYouChar:
                printCharacter VALUE
                call getCursorPosition
                mov bh,pos
                mov chatModeYouCursorX,bh
                mov bh,pos+1
                mov chatModeYouCursorY,bh
    popa


    ;; check if we need to transmit something
    continueToTransmit:
    pusha
        mov bh,chatModeMeCursorX
        mov pos,bh
        mov bh,chatModeMeCursorY
        mov pos+1,bh
        call setCursorPosition
    popa

    call UART_transmit
    cmp tra_bool,1
    jnz existTransmit
    mov ah, 6
    mov dl, 255
    int 21h 
    jz existTransmit
    mov tra_bool,0
    cmp al,13
    jne print_character2

    inc pos+1
    mov pos,0
    call setCursorPosition
    mov chatModeMeCursorX,0
    mov bh,pos+1
    mov chatModeMeCursorY,bh
    ;If empty put the VALUE in Transmit data register
    mov dx , 3F8H		; Transmit data register
    out dx , al 
    jmp existTransmit

    print_character2:
        printCharacter al
        call getCursorPosition
        mov bh,pos
        mov chatModeMeCursorX,bh
        mov bh,pos+1
        mov chatModeMeCursorY,bh
        pusha
            ;If empty put the VALUE in Transmit data register
            mov dx , 3F8H		; Transmit data register
            out dx , al 
        popa
        mov al,0

    existTransmit:
    jmp chatOuterLoop
startChatMode endp