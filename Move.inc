moveArrow proc
    ;check loop is for getting the key pressed without waiting for it
    CHECK:  
            mov ah,1 
            int 16h
            jz CHECK 
    ;Once we detect that the user pressed a key we need to consume it from the buffer
    ;so we will use the following interrupt
    mov ah,0
    int 16h 

    cmp ah,11h ;compare the scancode of the the key that we got to that of the W-key
    je moveUp

    cmp ah,1fh ;compare the scancode of the the key that we got to that of the S-key
    je moveDown

    cmp ah,20h  ;compare the scancode of the the key that we got to that of the D-key
    je moveRight

    cmp ah,1eh ;compare the scancode of the the key that we got to that of the A-key
    je moveLeft

    ret
    moveUp:
           mov ax,arrowPointer 
           dec ax               ;To move the arrowPointer up we will need to dec the row number
           mov tempNewArrowptr,ax ;We will store it temporarily because we will need it later
           call checkGridBorders ;check that the new position of arrowPointer is within the grid range
           cmp ch,0              
           je return            ;if the new arrowPosition is out of range we won't do anything so we would return
           call redrawOldArrowPos;To redraw the old ArrowPosition with its default color in the grid
           mov ax,tempNewArrowptr
           mov arrowPointer,ax  ;update the arrowPointer position with the new position
           jmp updateGrid      ;jmp to updateGrid reDraw the grid and the pieces

    moveDown:
             mov ax,arrowPointer
             inc ax
             mov tempNewArrowptr,ax
             call checkGridBorders
             cmp ch,0
             je return
             call redrawOldArrowPos
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
               call redrawOldArrowPos
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
               call redrawOldArrowPos
               mov ax,tempNewArrowptr
               mov arrowPointer+2,ax
               jmp updateGrid

    updateGrid: call redrawNewArrowPos
 return:   ret
moveArrow ENDP

;Update the grid matrix (initGrid) which contains the colors of the square background
;with the color of the arrowPointer at the new position
;The following proc aims at getting the position of the arrowPointer in initGrid matrix
;by this equation  initGrid+(row*8+column)
redrawNewArrowPos proc
    mov ax,arrowPointer ;get the row index of the arrowPointer
    mov di,arrowPointer+2 ;get the column index  of the arrowPointer
    lea bx,initGrid ;store the address of initGrid
    mov si,8        
    mul si          ;multiply ax by 8
    add bx,ax       ;then adding it to initGrid starting position
    add bx,di       ;then adding it to the column index to get the exact starting index of arrowPointer
    mov al,greenEnc  ;setting the color of that position to green
    mov [bx],al     ;update the grid background matrix with the new color encoding(green)
    ;reDrawing the grid after the update
    mov tempColor,al ;storing the new color in tempColor to be passed to the next proc
    call updateSquareBackgroundAndPiece
    ret
redrawNewArrowPos endp


;check that the new ArrowPosition is within the Grid Range
checkGridBorders proc
    cmp ax,7d
    jg outOfRange ;if it is greater than 7 then it is out of range

    cmp ax,0
    jl outOfRange ;if it is lower than 0 then it is out of range
    
    mov ch,1       ;set a flag indicating that it is within the range
    ret

    outOfRange:mov ch,0 ;set a flag indicating that it is out of Range
    ret
checkGridBorders Endp

;recoloring old Arrow position with the original color of the backgroud (grey and white)
;by comparing DefGrid (which contains the exact color of each square in grey and white)
;with initGrid (which contains the colors of the background that we draw)
redrawOldArrowPos proc
    ;get the aimed position that we want to compare 
    ;by DefGrid+(row*8+column)
    mov ax,arrowPointer ;storing the row number
    mov di,arrowPointer+2 ;storing the column number
    lea bx,DefGrid
    mov si,8
    mul si
    add bx,ax
    add bx,di 
    mov ch,[bx] ;store the color that we want
    
    ;initGrid+(row*8+column)
    mov ax,arrowPointer
    mov di,arrowPointer+2
    lea bx,initGrid
    mov si,8
    mul si
    add bx,ax
    add bx,di 
    mov [bx],ch ;replace the current color of old arrowPosition with its original default color stored in ch
                ;that we got from DefGrid
    mov tempColor,ch
    call updateSquareBackgroundAndPiece


    
    ret
redrawOldArrowPos endp 

;get the piece pos that we want to redraw
getPiecePosToDraw proc
    ;pieceToRedraw= initPiecePos*row+column
    mov ax,arrowPointer ;storing the row number
    mov di,arrowPointer+2 ;storing the column number
    lea bx,initPiecePos
    mov si,8
    mul si
    add bx,ax
    add bx,di 
    mov cl,[bx] ;store the piece that we want in cl to be used in updateSquareBackgroundAndPiece proc
    ret
getPiecePosToDraw endp

;get the starting pixel position of redrawing 
getPixelStartPosToDraw proc
    ;startPixelRow= arrowPointerRow*25
    ;startPixelColumn= arrowPointerColumn*25
    mov ax,arrowPointer
    mov dx,25d
    mul dx
    mov di,ax ;storing the row in di as the drawing proc require

    mov ax,arrowPointer+2
    mov dx,25d
    mul dx
    mov si,ax ;storing the column in si as the drawing proc require
    
    ret
getPixelStartPosToDraw endp

;getting the exact pos of the new piece and the exact starting position of pixel redrawing
;then calling the drawing procedures to draw them
updateSquareBackgroundAndPiece proc
    
    call getPiecePosToDraw 
    call getPixelStartPosToDraw
    mov al,tempColor ;storing the background color encoding in al so that the next procedure can use the suitable interrupt to draw it
    pusha
    call determineCubeColor
    popa
    mov al,cl   ;mov the piece that we stored in cl to al (stored earlier in getPiecePosToDraw proc)
    call determinePiece

    ret
updateSquareBackgroundAndPiece endp