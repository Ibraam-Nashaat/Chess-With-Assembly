modes proc far
mov ax,@data
mov ds,ax
;Clean screen
mov ax,0600h
mov bh,07 
mov cx,0 
mov dx,184FH
int 10h
;move cursor to 25,09
mov ah,2
mov bh,0
mov dl,25
mov dh,09
int 10h
; display message_name
mov ah, 9
mov dx, offset chatting_mode
int 21h
;move cursor to 25,11
mov ah,2
mov bh,0
mov dl,25
mov dh,11
int 10h
; display message_name
mov ah, 9
mov dx, offset game_mode
int 21h
;move cursor to 25,12
mov ah,2
mov bh,0
mov dl,25
mov dh,13
int 10h
; display message_name
mov ah, 9
mov dx, offset end_game
int 21h
;press the key
mov ah,0
 int 16h
;conditions
;F1
mov bl,3Bh
cmp ah,bl
jz Clean
;F2
mov bl,3Ch
cmp ah,bl
jz Clean
;ESC
mov bl,01
cmp ah,bl
jz exit
Clean:mov ax,0600h
mov bh,07 
mov cx,0 
mov dx,184FH
int 10h
ret
 exit:
    mov ah , 4ch
    int 21h
    
     modes endp
