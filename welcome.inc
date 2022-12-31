welcome_window proc far 
;Clear screen
mov ax,0600h
mov bh,07 
mov cx,0 
mov dx,184FH
int 10h

;move cursor to 0,0
mov ah,2
mov bh,0
mov dx,0000h
int 10h
; display message_name
printMsg msg_name
;move cursor to 0A line
mov ah,2
mov bh,0
mov dx,0A00h
int 10h
; display msg_startGame
printMsg msg_startGame

;move cursor to second line
mov ah,2
mov bh,0
mov dx,0105h
int 10h
; get the name
mov ah,0AH 
mov dx,offset firstPlayerBuffer
int 21h
mov si , offset firstPlayerName
mov dl,[si]
;check below Z
checkATOZ:
    mov cl,'Z'
    cmp dl,cl ;check if between A,Z
    jbe above
    jmp checkaTOzsmall

above:
   mov cl,'A'
   cmp dl,cl
    jae clear1

checkaTOzsmall:
   mov al,'z'
    cmp dl,al     ;check if between a,z
    jbe below
below:
    mov al,'a'
    cmp dl,al
    jae clear1 

    mov cl,escEnc
returnFromWelcome:ret
; if you want to move to another page change clear
;if name is valid go to clear else exit    
clear1:
mov ax,0600h
mov bh,07 
mov cx,0 
mov dx,184FH
int 10h
mov cl,5
ret
welcome_window endp
