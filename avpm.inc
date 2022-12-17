;Available piece moves
;This file contains the following procedures:
;   1)bishopAvMoves
;   2)rookAvMoves
;   3)queenAvMoves
;   4)kingAvMoves
;   5)diagonalMoves
;   6)axialMoves
;   7)knightAvMoves
bishopAvMoves proc
    call diagonalMoves
    ret
bishopAvMoves endp

rookAvMoves proc
    call axialMoves
    ret
rookAvMoves endp

queenAvMoves proc
    call diagonalMoves
    call axialMoves
    ret
queenAvMoves endp

kingAvMoves proc
    mov al,blueEnc  ;setting the color of that position to green
    mov tempColor,al ;storing the new color in tempColor to be passed to the next proc
    mov ax,arrowPointer ;row
    mov di,arrowPointer+2;column
    lea bx,initGrid
    
    KingEast: 
        add di,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initKingSouth

        ; Checking if the next position has a piece of the same color
        call getPieceInPos
        mov tempFromPiece, cl

        mov ax, tempRow
        mov di, tempColumn

        call getPieceInPos
        mov tempToPiece, cl

        call isValidPossibleMove
        cmp ch, 1
        jne initKingSouth
        call setSquareColor

    initKingSouth: 
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    kingSouth:
        add ax,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        ; Checking if the next position is within the grid borders
        call checkGridBorders2
        cmp ch,1
        jne initKingNorth
        ; Checking if the next position has a piece of the same color
        call getPieceInPos
        mov tempFromPiece, cl

        mov ax, tempRow
        mov di, tempColumn

        call getPieceInPos
        mov tempToPiece, cl

        call isValidPossibleMove
        cmp ch, 1
        jne initKingNorth
        
        call setSquareColor

    initKingNorth:
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    KingNorth:
        sub ax,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initKingWest

        ; Checking if the next position has a piece of the same color
        call getPieceInPos
        mov tempFromPiece, cl

        mov ax, tempRow
        mov di, tempColumn

        call getPieceInPos
        mov tempToPiece, cl

        call isValidPossibleMove
        cmp ch, 1
        jne initKingWest

        call setSquareColor

    initKingWest:
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    kingWest:
        sub di,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initKingNorthEast

        ; Checking if the next position has a piece of the same color
        call getPieceInPos
        mov tempFromPiece, cl

        mov ax, tempRow
        mov di, tempColumn

        call getPieceInPos
        mov tempToPiece, cl

        call isValidPossibleMove
        cmp ch, 1
        jne initKingNorthEast

        call setSquareColor
   
    initKingNorthEast:
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    kingNorthEast:
        sub ax,1
        add di,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initKingNorthWest
        ; Checking if the next position has a piece of the same color
        call getPieceInPos
        mov tempFromPiece, cl

        mov ax, tempRow
        mov di, tempColumn

        call getPieceInPos
        mov tempToPiece, cl

        call isValidPossibleMove
        cmp ch, 1
        jne initKingNorthWest

        call setSquareColor 

    initKingNorthWest:
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    kingNorthWest:
        sub ax,1
        sub di,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initKingSouthEast
        ; Checking if the next position has a piece of the same color
        call getPieceInPos
        mov tempFromPiece, cl

        mov ax, tempRow
        mov di, tempColumn

        call getPieceInPos
        mov tempToPiece, cl

        call isValidPossibleMove
        cmp ch, 1
        jne initKingSouthEast

        call setSquareColor

    initKingSouthEast:
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    kingSouthEast:
        add ax,1
        add di,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initKingSouthWest
        ; Checking if the next position has a piece of the same color
        call getPieceInPos
        mov tempFromPiece, cl

        mov ax, tempRow
        mov di, tempColumn

        call getPieceInPos
        mov tempToPiece, cl

        call isValidPossibleMove
        cmp ch, 1
        jne initKingSouthWest

        call setSquareColor

    initKingSouthWest:
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    KingSouthWest:
        add ax,1
        sub di,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne returnKing
        ; Checking if the next position has a piece of the same color
        call getPieceInPos
        mov tempFromPiece, cl

        mov ax, tempRow
        mov di, tempColumn

        call getPieceInPos
        mov tempToPiece, cl

        call isValidPossibleMove
        cmp ch, 1
        jne returnKing

        call setSquareColor
            

   returnKing: popa
                ret
    ret
kingAvMoves endp



diagonalMoves proc far
    
    mov al,blueEnc  ;setting the color of that position to green
    mov tempColor,al ;storing the new color in tempColor to be passed to the next proc
    mov ax,arrowPointer ;row
    mov di,arrowPointer+2;column
    lea bx,initGrid
    
    northEast:
        sub ax,1
        add di,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initNorthWest
        ; Checking if the next position has a piece of the same color
        call getPieceInPos
        mov tempFromPiece, cl

        mov ax, tempRow
        mov di, tempColumn

        call getPieceInPos
        mov tempToPiece, cl

        call isValidPossibleMove
        cmp ch, 1
        jne initNorthWest

        call setSquareColor
        popa 
        jmp northEast

    initNorthWest:
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    northWest:
        sub ax,1
        sub di,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initSouthEast
        ; Checking if the next position has a piece of the same color
        call getPieceInPos
        mov tempFromPiece, cl

        mov ax, tempRow
        mov di, tempColumn

        call getPieceInPos
        mov tempToPiece, cl

        call isValidPossibleMove
        cmp ch, 1
        jne initSouthEast

        call setSquareColor
        popa 
        jmp northWest


    initSouthEast:
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    southEast:
        add ax,1
        add di,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initSouthWest
        ; Checking if the next position has a piece of the same color
        call getPieceInPos
        mov tempFromPiece, cl

        mov ax, tempRow
        mov di, tempColumn

        call getPieceInPos
        mov tempToPiece, cl

        call isValidPossibleMove
        cmp ch, 1
        jne initSouthWest

        call setSquareColor
        popa 
        jmp southEast

    initSouthWest:
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    southWest:
        add ax,1
        sub di,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne return1
        ; Checking if the next position has a piece of the same color
        call getPieceInPos
        mov tempFromPiece, cl

        mov ax, tempRow
        mov di, tempColumn

        call getPieceInPos
        mov tempToPiece, cl

        call isValidPossibleMove
        cmp ch, 1
        jne return1
        call setSquareColor
        popa 
        jmp southWest

    return1: 
        popa
        ret

   ret
diagonalMoves ENDP

axialMoves proc far
    
    mov al,blueEnc  ;setting the color of that position to green
    mov tempColor,al ;storing the new color in tempColor to be passed to the next proc
    mov ax,arrowPointer ;row
    mov di,arrowPointer+2;column
    lea bx,initGrid
    
    east:    
        add di,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initSouth
        ; Checking if the next position has a piece of the same color
        call getPieceInPos
        mov tempFromPiece, cl

        mov ax, tempRow
        mov di, tempColumn

        call getPieceInPos
        mov tempToPiece, cl

        call isValidPossibleMove
        cmp ch, 1
        jne initSouth

        call setSquareColor
        popa 
        jmp east

    initSouth:
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    south:
        add ax,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initNorth
        ; Checking if the next position has a piece of the same color
        call getPieceInPos
        mov tempFromPiece, cl

        mov ax, tempRow
        mov di, tempColumn

        call getPieceInPos
        mov tempToPiece, cl

        call isValidPossibleMove
        cmp ch, 1
        jne initNorth

        call setSquareColor
        popa 
        jmp south

    initNorth:
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    north:
        sub ax,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initWest
        ; Checking if the next position has a piece of the same color
        call getPieceInPos
        mov tempFromPiece, cl

        mov ax, tempRow
        mov di, tempColumn

        call getPieceInPos
        mov tempToPiece, cl

        call isValidPossibleMove
        cmp ch, 1
        jne initWest

        call setSquareColor
        popa 
        jmp north

    initWest:
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    west:
        sub di,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne returnAxial
        ; Checking if the next position has a piece of the same color
        call getPieceInPos
        mov tempFromPiece, cl

        mov ax, tempRow
        mov di, tempColumn

        call getPieceInPos
        mov tempToPiece, cl

        call isValidPossibleMove
        cmp ch, 1
        jne returnAxial
        
        call setSquareColor
        popa 
        jmp west

    returnAxial: 
        popa
        ret

   ret
axialMoves ENDP

knightAvMoves proc
    mov al,blueEnc  ;setting the color of that position to green
    mov tempColor,al ;storing the new color in tempColor to be passed to the next proc
    
    lea bx,initGrid

    mov ax,arrowPointer ;row
    mov di,arrowPointer+2;column
    
    knightMove1:
        add di,2
        add ax, 1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initKnightMove2
        call setSquareColor

    initKnightMove2: 
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    knightMove2:
        add di,2
        sub ax, 1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initKnightMove3
        call setSquareColor

    initKnightMove3: 
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    knightMove3:
        add ax,2
        add di, 1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initKnightMove4
        call setSquareColor

    initKnightMove4:
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    knightMove4:
        add ax,2
        sub di, 1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initKnightMove5
        call setSquareColor
   
    initKnightMove5:
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    knightMove5:
        sub di,2
        add ax,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initKnightMove6
        call setSquareColor
         
    initKnightMove6: 
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    knightMove6:
        sub di,2
        sub ax,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initKnightMove7
        call setSquareColor

    initKnightMove7: 
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    knightMove7:
        sub ax,2
        sub di,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initKnightMove8
        call setSquareColor


     initKnightMove8:
        popa
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    KnightMove8:
        sub ax,2
        add di,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne returnKnight
        call setSquareColor
            
    returnKnight:
        popa
        ret

    ret
knightAvMoves endp



