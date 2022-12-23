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