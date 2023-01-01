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
    mov dx , 3FDH ; Line Status Register
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
    mov dx , 3FDH		; Line Status Register
    in al , dx 
    and al , 1
    jz ex2
    mov rec_bool,1
    ex2:
popa
ret
UART_rec endp

clearBuffer proc 
    push ax
    mov ah,0
    int 16h      
    pop ax
clearBuffer endp

; Sends a byte through serial port
sendByte macro valueToSend
push ax
    mov al, valueToSend
    mov dx , 3F8H   ; Transmit FirstPlayerSignal
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

sendCharacterViaSerial proc NEAR
    push AX
    push dx
    @@SendingName:       
    mov dx,03FDh        
    in al,dx
    TEST al, 00100000b  
    jz @@SendingName
    mov dx, 3F8H
    mov al, sendParameter
    OUT dx, al
    pop dx
    pop AX
    ret
sendCharacterViaSerial endp

receiveCharacterFromSerial proc NEAR
    push dx
    push AX  
    mov dx, 3FDH
    in al, dx
    and al, 1
    jz exitReceiveChar
    mov dx, 3F8H
    in al, dx
    mov receiveParameter,al
    exitReceiveChar:
    pop AX
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

exchangePlayersNames proc NEAR
    sendByte startExchangeSignal
    waitForExchangeSignalFromOtherPlayer:
    mov dx, 3FDH
    in al, dx
    and al, 1
    jz waitForExchangeSignalFromOtherPlayer
    call receiveCharacterFromSerial
    mov al, startExchangeSignal
    cmp receiveParameter, al
    je prepareNames
    jmp waitForExchangeSignalFromOtherPlayer
    prepareNames:
    ;call sendCharacterViaSerial
    mov si, offset firstPlayerName
    mov DI, offset secondPlayerName
    mov cx, 14
    sendYourName:
    mov al, [si]
    mov sendParameter, al
    call sendCharacterViaSerial
    inc si
    checkIfReceivedName:
    mov dx, 3FDH
    in al, dx
    and al, 1
    jz checkIfReceivedName
    call receiveCharacterFromSerial
    mov al, receiveParameter
    mov [DI] , al
    inc DI
    loop sendYourName

    mov BX, 0
    getSecondPlayerNameLength:
    cmp secondPlayerName[BX], '$'
    je finishGettingOtherPlayerName
    inc BX
    jmp getSecondPlayerNameLength
    finishGettingOtherPlayerName:
    mov secondPlayerNameSize, Bl
    ret
exchangePlayersNames endp

handleGameSendAndReceive proc
pusha
    
    mov al,"%"
    mov sendParameter, al
    call sendMoveViaSerial

    @waitForExchangeSignal:
    mov dx, 3FDH
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
    mov dx, 3FDH
    in al, dx
    and al, 1
    jz @Receive
    call receiveMoveFromSerial
    mov al, receiveParameter
    mov [di] , al
    inc di
    loop @Send    
   
   mov al,receivedData
    cmp al,0FFh
    je checkIfCharWasSend
    call moveReceivedPiece

    checkIfCharWasSend:
    mov al,receivedData+4
    cmp al,0FFh
    je @return
    mov VALUE,al
    call printReceivedChar

    


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
    mov dx, 3FDH
    in al, dx
    and al, 1
    jz exitReceiveMove
    mov dx, 3F8H
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
    mov dx, 3F8H
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