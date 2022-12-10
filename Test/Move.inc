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
           mov tempNewArrowptr,ax
           call checkGridBorders
           cmp ch,0
           je return
           call recolorOldArrowPos
           mov ax,tempNewArrowptr
           mov arrowPointer,ax
           jmp updateGrid

    moveDown:
             mov ax,arrowPointer
             inc ax
             mov tempNewArrowptr,ax
             call checkGridBorders
             cmp ch,0
             je return
             call recolorOldArrowPos
             mov ax,tempNewArrowptr
             mov arrowPointer,ax
             jmp updateGrid


    moveRight: 
               mov ax,arrowPointer+2
               inc ax
               mov tempNewArrowptr,ax
               call checkGridBorders
               cmp ch,0
               je return
               call recolorOldArrowPos
               mov ax,tempNewArrowptr
               mov arrowPointer+2,ax
               jmp updateGrid

    moveLeft: 
               mov ax,arrowPointer+2
               dec ax
               mov tempNewArrowptr,ax
               call checkGridBorders
               cmp ch,0
               je return
               call recolorOldArrowPos
               mov ax,tempNewArrowptr
               mov arrowPointer+2,ax
               jmp updateGrid

    updateGrid: mov ax,arrowPointer
                mov di,arrowPointer+2
                lea bx,initGrid
                mov si,8
                mul si
                add bx,ax
                add bx,di 
                mov ah,greenEnc
                mov [bx],ah
                call Draw

    
 return:   ret
moveArrow ENDP

checkGridBorders proc
    cmp ax,7d
    jg outOfRange

    cmp ax,0
    jl outOfRange
    
    mov ch,1
    ret

    outOfRange:mov ch,0
    ret
checkGridBorders Endp


recolorOldArrowPos proc
        mov ax,arrowPointer
        mov di,arrowPointer+2
        lea bx,DefGrid
        mov si,8
        mul si
        add bx,ax
        add bx,di 
        mov ch,[bx]
        
        mov ax,arrowPointer
        mov di,arrowPointer+2
        lea bx,initGrid
        mov si,8
        mul si
        add bx,ax
        add bx,di 
        mov [bx],ch
    ret
recolorOldArrowPos endp 