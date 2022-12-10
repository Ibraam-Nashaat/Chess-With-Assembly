moveArrow proc
    CHECK:  
            mov ah,1 
            int 16h
            jz CHECK 
    mov ah,0
    int 16h 

    cmp ah,11h ;up
    je moveUp

    cmp ah,1fh
    je moveDown

    cmp ah,20h
    je moveRight

    cmp ah,1eh
    je moveLeft

    ret
    moveUp:
           mov ax,arrowPointer
           dec ax
           mov arrowPointer,ax
           jmp updateGrid

    moveDown:
             mov ax,arrowPointer
             inc ax
             mov arrowPointer,ax
             jmp updateGrid

    moveRight: 
               mov ax,arrowPointer+2
               inc ax
               mov arrowPointer+2,ax
               jmp updateGrid

    moveLeft: 
               mov ax,arrowPointer+2
               dec ax
               mov arrowPointer+2,ax
               jmp updateGrid

    updateGrid: mov ax,arrowPointer
                mov di,arrowPointer+2
                lea bx,initGrid
                mov si,8
                mul si
                add bx,ax
                add bx,di 
                mov ah,2
                mov [bx],ah
                call Draw

    
    ret
moveArrow ENDP