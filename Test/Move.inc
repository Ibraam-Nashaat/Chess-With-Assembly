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
           pusha
           call checkGridBorders
           cmp ch,0
           je j
           mov ax,arrowPointer
           mov bx,arrowPointer+2
           call recolorOldArrowPos
           popa
           mov arrowPointer,ax
           jmp updateGrid

    moveDown:
             mov ax,arrowPointer
             inc ax
             pusha
             call checkGridBorders
             cmp ch,0
             je return
             mov ax,arrowPointer
             mov bx,arrowPointer+2
             call recolorOldArrowPos
             popa
             mov arrowPointer,ax
             jmp updateGrid

        j:ret

    moveRight: 
               mov ax,arrowPointer+2
               inc ax
               pusha
               call checkGridBorders
               cmp ch,0
               je return
               mov ax,arrowPointer+2
               mov bx,arrowPointer
               call recolorOldArrowPos
               popa
               mov arrowPointer+2,ax
               jmp updateGrid

    moveLeft: 
               mov ax,arrowPointer+2
               dec ax
               pusha
               call checkGridBorders
               cmp ch,0
               je return
               mov ax,arrowPointer+2
               mov bx,arrowPointer
               call recolorOldArrowPos
               popa
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
    mov ch,2d
    div ch
    cmp ah,0
    je nextGreyValid

    mov ax,bx
    mov ch,2d
    div ch
    cmp ah,0
    jne recolorToGrey

    recolorToWhite:mov ax,arrowPointer
                 mov di,arrowPointer+2
                 lea bx,initGrid
                 mov si,8
                 mul si
                 add bx,ax
                 add bx,di 
                 mov ah,whiteEnc
                 mov [bx],ah
                 ret




    nextGreyValid:mov ax,bx
                  mov ch,2d
                  div ch
                  cmp ah,0
                  je recolorToGrey

    recolorToGrey:mov ax,arrowPointer
                 mov di,arrowPointer+2
                 lea bx,initGrid
                 mov si,8
                 mul si
                 add bx,ax
                 add bx,di 
                 mov ah,greyEnc
                 mov [bx],ah
    ret
recolorOldArrowPos endp 