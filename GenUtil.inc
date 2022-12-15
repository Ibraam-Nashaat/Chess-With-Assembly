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
    ;pieceToRedraw= initPiecePos*row+column
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



setSquareColor proc
    mov si,8        
    mul si          ;multiply ax by 8
    add bx,ax       ;then adding it to initGrid starting position
    add bx,di       ;then adding it to the column index to get the exact starting index of arrowPointer
    mov al,tempColor
    mov [bx],al     ;update the grid background matrix with the new color encoding
    cmp al,blueEnc
    jne notBlue

    call setDefaultGridAfterClick

    ;reDrawing the grid after the update
    notBlue:call updateSquareBackgroundAndPiece
    ret

    ret
setSquareColor endp



setDefaultGridAfterClick proc
    mov ax,tempRow
    mov di,tempColumn
    lea bx,defGrid
    mov si,8        
    mul si          ;multiply ax by 8
    add bx,ax       ;then adding it to initGrid starting position
    add bx,di       ;then adding it to the column index to get the exact starting index of arrowPointer
    mov al,tempColor
    mov [bx],al     ;update the grid background matrix with the new color encoding
    ret
setDefaultGridAfterClick endp




resetDefGridAfter2ndClick proc
    lea bx,defGrid
    lea si,stdGrid
    mov cx,0

        loopDefGrid:        mov dl,[bx]
                            pusha
                            cmp dl,[si]
                            jne changeColor
        contLoopDefGrid :   popa
                            add si,1
                            add bx,1
                            inc cx
                            cmp cx,64d
                            jne loopDefGrid
    ret

    changeColor:mov al,[si]
                mov [bx],al
                mov ax,cx
                mov cx,8d
                div cx
                mov tempRow,ax
                mov tempColumn,dx
                mov di,dx
                mov bl,[si]
                mov tempColor,bl
                lea bx,defGrid
                call updateSquareBackgroundAndPiece
                jmp contLoopDefGrid
    ret
resetDefGridAfter2ndClick endp



checkClickCount proc
    mov al,clickCount
    cmp al,0
    je click1

    mov al,0
    mov clickCount,al
    call resetDefGridAfter2ndClick
    ret
    click1:inc al
           mov clickCount,al
           call getClickedPiece
    ret
checkClickCount endp