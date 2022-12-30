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

UART_transmit proc
pusha
    mov dx , 3FDH ; Line Status Register
    In al , dx ;Read Line Status

    AND al , 00100000b
    jz ex1
    mov tra_bool,1;indication

    ex1:

popa
ret
UART_transmit endp

UART_rec proc
pusha
    ;Check that Data Ready
    mov dx , 3FDH		; Line Status Register
    in al , dx 
    AND al , 1
    jz ex2
    mov rec_bool,1
    ex2:
popa
ret
UART_rec endp

; Check is first player:
;   send byte "S for sent" as a signal
;   wait for byte "R for received"  as a signal
; Check if second player:
;   check for "S" signal
;   send "R" signal
assignColorAndSignal proc
pusha
    ;Clear the screen
    mov ax,3
    int 10h

    mov pos,0 ;x
    mov pos+1,0 ;y
    call setCursorPosition

    printMsg welcome_msg
    mov pos,9 ;x
    call setCursorPosition
    printMsg bufferName

    mov pos,0 ;x
    mov pos+1,1 ;y
    call setCursorPosition
    printMsg waiting_msg

    call UART_rec
    cmp rec_bool, 0
    ; First Player 
    je firstPlayerPath
    ; Second Player
    secondPlayerPath:
        mov isBlack, 1
        
        ; Get the byte in serial
        mov dx , 03F8H
        in al , dx 
        mov VALUE , al
        ; Check if it's the right signal from player1
        cmp al, firstPlayerSignal
        jne failedSettingUpColor

        ifSecondPlayerCanSendSignal:
            call UART_transmit
            cmp tra_bool, 1 ; If I can send Signal
            jne ifSecondPlayerCanSendSignal

        mov al, secondPlayerSignal
        mov dx , 3F8H   ; Transmit SecondPlayerSignal
        out dx , al

    jmp finishedSettingUpColor

    firstPlayerPath:
        mov isBlack, 0

        mov al, firstPlayerSignal
        mov dx , 3F8H   ; Transmit FirstPlayerSignal
        out dx , al

        ifFirstPlayerReceivedSignal:
            call UART_rec
            cmp rec_bool, 1 ; If I can send Signal
            jne ifFirstPlayerReceivedSignal

        ; Get the byte in serial
        mov dx , 03F8H
        in al , dx 
        mov VALUE , al
        ; Check if it's the right signal from player1
        cmp al, secondPlayerSignal
        je finishedSettingUpColor

    failedSettingUpColor:
        jmp exit

    finishedSettingUpColor:
popa
ret
assignColorAndSignal endp