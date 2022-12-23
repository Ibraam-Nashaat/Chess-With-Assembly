getCursorPosition proc
pusha
;; get cursor position
mov ah,3h
mov bh,0h
int 10h
;; store the current line in pos+1 and the current colummn in pos
mov pos,dl
mov pos+1,dh
popa
ret
getCursorPosition endp

setCursorPosition proc
pusha
mov   dh,pos+1
mov   dl,pos
mov   bh,0
mov   ah,2
int   10h
popa
ret
setCursorPosition endp

printCharacter macro c
pusha
mov ah,2 
mov dl,c
int 21h
popa      
endm

printMsg macro message
pusha
mov ah,9
mov dx,offset message
int 21h
popa
endm