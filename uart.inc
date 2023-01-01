UART_init proc 
pusha
    ; init COM

    ;Set Divisor Latch Access Bit
    mov dx,3fbh 			; Line Control Register
    mov al,10000000b		;Set Divisor Latch Access Bit
    out dx,al				;Out it

    ;Set LSB byte of the Baud Rate Divisor Latch register.
    mov dx,3f8h			
    mov al,0ch			
    out dx,al

    ;Set MSB byte of the Baud Rate Divisor Latch register.
    mov dx,3f9h
    mov al,00h
    out dx,al

    ;Set port configuration
    mov dx,3fbh
    mov al,00011011b
    out dx,al

popa
ret
UART_init endp

; Sets tra_bool to 1 if we can send a byte
UART_transmit proc
pusha
    mov dx , 3fdh ; Line Status Register
    in al , dx ;Read Line Status

    and al , 00100000b
    jz ex1
    mov tra_bool,1;indication

    ex1:

popa
ret
UART_transmit endp

; Sets rec_bool to 1 if we can receive a byte
UART_rec proc
pusha
    ;Check that Data Ready
    mov dx , 3fdh		; Line Status Register
    in al , dx 
    and al , 1
    jz ex2
    mov rec_bool,1
    ex2:
popa
ret
UART_rec endp

; Sends a byte through serial port
sendByte macro valueToSend
push ax
    mov al, valueToSend
    mov dx , 3f8h   ; Transmit FirstPlayerSignal
    out dx , al
pop ax
endm 

; Receives a byte from serial port to VALUE
receiveByte proc
push ax
    mov dx , 03F8H
    in al , dx 
    mov VALUE , al
pop ax
ret
receiveByte endp

; Send when allowed (Wait until allowed)
sendCharacterViaSerial proc
    push ax
    push dx

    checkIfCanSend:       
        mov dx,03FDh
        in al,dx
        TEST al, 00100000b
        jz checkIfCanSend
    mov dx, 3f8h
    mov al, sendParameter
    out dx, al

    pop dx
    pop ax
    ret
sendCharacterViaSerial endp

; receive character if there is one
receiveCharacterFromSerial proc 
    push dx
    push ax

    mov dx, 3fdh
    in al, dx
    and al, 1
    jz exitReceiveChar

    mov dx, 3f8h
    in al, dx
    mov receiveParameter,al

    exitReceiveChar:
        pop ax
        pop dx
    ret
receiveCharacterFromSerial endp

assignPiecesColor proc
pusha
    call UART_rec
    cmp rec_bool, 0
    ; First Player 
    je firstPlayerPath
    ; Second Player
    secondPlayerPath:
        mov isBlack, 1
        jmp finishedSettingUpColor

    firstPlayerPath:
        mov isBlack, 0

    finishedSettingUpColor:
popa
ret
assignPiecesColor endp

exchangePlayersNames proc 
    ; Send Signal to start exchanging names
    sendByte startExchangeSignal

    ; Wait the other player to resend the same signal
    waitForExchangeSignalFromOtherPlayer:
        mov dx, 3fdh
        in al, dx
        and al, 1
        jz waitForExchangeSignalFromOtherPlayer

    ; Get the character the other player sent in serial
    call receiveCharacterFromSerial
    mov al, startExchangeSignal
    cmp receiveParameter, al
    ; If the signal is right I send my name the receive the other's
    je prepareNames

    ; If we get another signal we wait until he sends the right one
    jmp waitForExchangeSignalFromOtherPlayer
    prepareNames:
        mov si, offset firstPlayerName
        mov di, offset secondPlayerName
        mov cx, 14

    mov al, 0
    mov secondPlayerNameSize, al

    ; Send my name and get other player's name  
    exchangeOperation:
        ; Si loops on my name to send it
        mov al, [si]
        mov sendParameter, al
        call sendCharacterViaSerial
        inc si
        checkIfReceivedName:
            mov dx, 3fdh
            in al, dx
            and al, 1
            jz checkIfReceivedName

        call receiveCharacterFromSerial
        mov al, receiveParameter
        ; di loops on other variable to save it
        mov [di] , al
        inc di
        inc secondPlayerNameSize
    loop exchangeOperation
    ret
exchangePlayersNames endp

handleGameSendAndReceive proc
pusha
    
    mov al,"%"
    mov sendParameter, al
    call sendMoveViaSerial

    @waitForExchangeSignal:
    mov dx, 3fdh
    in al, dx
    and al, 1
    jz @waitForExchangeSignal
    call receiveMoveFromSerial
    cmp receiveParameter, "%"
    je @IsSend
    jmp @waitForExchangeSignal
   
    @IsSend:
    mov cx,5
    lea si,dataToSend
    lea di,receivedData


    @Send:
    mov al, [si]
    mov sendParameter, al
    call sendMoveViaSerial
    inc si
    @Receive:
    mov dx, 3fdh
    in al, dx
    and al, 1
    jz @Receive
    call receiveMoveFromSerial
    mov al, receiveParameter
    mov [di] , al
    inc di
    loop @Send    
   
    mov al,receivedData
    cmp al,"#"
    je @OtherSideExited

    cmp al,0FFh
    je checkIfCharWasSend
    call moveReceivedPiece
 
    checkIfCharWasSend:
    mov al,receivedData+4
    cmp al,0FFh
    je @return
    mov VALUE,al
    call printReceivedChar

    jmp @return

    @OtherSideExited:mov al,1d
                     mov exitFlagFromOtherSide,al


 @return:mov al,0FFh
         mov sendParameter, al
       ;  call sendMoveViaSerial
         mov receiveParameter,0
         mov al,0FFh
        mov dataToSend,al
        mov dataToSend+4,al
popa
ret
handleGameSendAndReceive endp

receiveMoveFromSerial proc
    push dx
    push AX  
    mov dx, 3fdh
    in al, dx
    and al, 1
    jz exitReceiveMove
    mov dx, 3f8h
    in al, dx
    mov receiveParameter,al
    exitReceiveMove:
    pop AX
    pop dx
    ret
receiveMoveFromSerial endp

sendMoveViaSerial proc
    push AX
    push dx
    @@SendingMove:       
    mov dx,03FDh        
    in al,dx
    TEST al, 00100000b  
    jz @@SendingMove
    mov dx, 3f8h
    mov al, sendParameter
    OUT dx, al
    pop dx
    pop AX
    ret
sendMoveViaSerial endp


moveReceivedPiece proc
pusha
        
        mov ah,0
        mov al,receivedData
        mov ch,0
        mov cl,receivedData+1
        mov di,cx
        mov tempRow,ax
        mov tempColumn,di
        call getPiecePosToDraw
        mov fromPieceEnc,cl
        mov cl,emptyEnc
        mov [bx],cl


        mov ax,tempRow
        mov di,tempColumn
        lea bx,stdGrid
        mov si,8        
        mul si          
        add bx,ax       
        add bx,di       
        mov al,[bx]
        mov tempColor,al  
        call updateSquareBackgroundAndPiece

       

        mov ah,0
        mov al,receivedData+2
        mov ch,0
        mov cl,receivedData+3
        mov di,cx
        mov tempRow,ax
        mov tempColumn,di
        call getPiecePosToDraw
        call incrementEatenPieces
        mov cl,fromPieceEnc
        call printGameInfo
        call checkIfKingIsEaten
        mov [bx],cl

        

        mov ax,tempRow
        mov di,tempColumn
        lea bx,stdGrid
        mov si,8        
        mul si          
        add bx,ax       
        add bx,di       
        mov al,[bx]
        mov tempColor,al  
        call updateSquareBackgroundAndPiece

                 
  popa
  ret

moveReceivedPiece endp