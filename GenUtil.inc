;General utilities across the program
;This file contains the following procedures:
;   1)getPiecePosToDraw
;   2)getPixelStartPosToDraw
;   3)updateSquareBackgroundAndPiece
;   4)setSquareColor
;   5)setDefaultGridAfterClick
;   6)resetDefGridAfter2ndClick
;   7)checkClickCount

;get the piece pos that we want to redraw
getPiecePosToDraw proc
    ;pieceToRedraw= initPiecePos+(8*row+column)
    mov ax,tempRow ;storing the row number
    mov di,tempColumn;storing the column number
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
    mov ax,tempRow
    mov dx,25d
    mul dx
    mov di,ax ;storing the row in di as the drawing proc require

    mov ax,tempColumn
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


;before calling this procedure you will need to pass
;   1)bx: containing the address of the grid
;   2)tempRow: containig the current row of the cell that you want to recolor
;   3)tempColumn: containing the current column of the cell that you want to recolor
;   4)tempColor: containing the background color encoding of the cell
setSquareColor proc
    ;get the exact position of the cell by 
    ;gridAddress+(8*tempRow+tempColumn)
    pusha
    mov ax,tempRow
    mov di,tempColumn
    lea bx,initGrid
    mov si,8        
    mul si          
    add bx,ax       
    add bx,di       
    mov al,tempColor
    mov [bx],al     ;update the grid background matrix with the new color encoding
    cmp al,blueEnc  
    jne notBlue

    call setDefaultGridAfterClick ;if the color encoding is blue then we will call this proc

    ;reDrawing the grid after the update if the current position is not blue
    notBlue:
        call updateSquareBackgroundAndPiece

    popa
    ret
setSquareColor endp


;This proc aims at recoloring the defGrid with blue cells
;To know the difference between defGrid,initGrid and stdGrid, Refer to the data segment comments.
setDefaultGridAfterClick proc
    ;Pos=defGrid+(8*tempRow+tempColumn)
    pusha
    mov ax,tempRow
    mov di,tempColumn
    lea bx,defGrid
    mov si,8        
    mul si          
    add bx,ax       
    add bx,di       
    mov al,tempColor
    mov [bx],al     ;update the grid background matrix with the new color encoding
    popa
    ret
setDefaultGridAfterClick endp



;reset defGrid back to grey and white by looping over defGrid and stdGrid and comparing
;the color encoding at each single position.
;If it is the same color then we will see the next position, otherwise we would recolor defGrid cell
;with its original grey and white color.
resetDefGridAfter2ndClick proc
    lea bx,defGrid
    lea si,stdGrid
    lea di,initGrid
    mov cx,0

    loopDefGrid:
        mov dl,[bx]
        pusha
        cmp dl,[si]
        jne changeColor

    contLoopDefGrid:
        popa
        add si,1
        add bx,1
        add di,1
        inc cx
        cmp cx,64d
        jne loopDefGrid
    ret

    changeColor:
        mov al,[si]
        mov [bx],al ;moving the color encoding of stdGrid to defGrid
        mov [di],al ;moving the color encoding of stdGrid to initGrid
        ;getting the exact position of the cell by
        ;row= cx/8
        ;column=cx%8
        mov ax,cx  
        mov cx,8d
        div cx
        mov tempRow,ax
        mov tempColumn,dx
        mov di,dx
        mov bl,[si]
        mov tempColor,bl
        lea bx,initGrid
        call updateSquareBackgroundAndPiece
        jmp contLoopDefGrid
    ret
resetDefGridAfter2ndClick endp


;Detect the current count of the Q-click to determine if we would get available moves(1st click)
;or (move or deactivate available moves(2nd click))
checkClickCount proc
    mov al,clickCount
    cmp al,0
    je click1 ;if it is the first click jmp to click1

    ;Otherwise it is the second click
    mov clickCount,0   ;reset the counter back to zero
    call resetDefGridAfter2ndClick 

    ret
    
    click1:
        inc al
        mov clickCount,al
        call getClickedPiece
    ret
checkClickCount endp