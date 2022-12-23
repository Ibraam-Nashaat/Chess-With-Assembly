;Available piece moves
;This file contains the following procedures:
;   1)bishopAvMoves
;   2)rookAvMoves
;   3)queenAvMoves
;   4)kingAvMoves
;   5)diagonalMoves
;   6)axialMoves
;   7)knightAvMoves
;   8)blackPawnAvMoves
;   9)whitePawnAvMoves
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
    
    
    KingEast: 
        mov tempRow,ax
        mov tempColumn,di
        add tempColumn,1

        call checkGridBorders2
        cmp ch,1
        jne kingSouth

        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je kingSouth
        call setSquareColor

    kingSouth:
        mov tempRow,ax
        mov tempColumn,di
        add tempRow,1

        ; Checking if the next position is within the grid borders
        call checkGridBorders2
        cmp ch,1
        jne kingNorth

        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je kingNorth
        
        call setSquareColor

    kingNorth:
        mov tempRow,ax
        mov tempColumn,di
        sub tempRow,1

        call checkGridBorders2
        cmp ch,1
        jne kingWest

        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je kingWest

        call setSquareColor

    kingWest:
        mov tempRow,ax
        mov tempColumn,di
        sub tempColumn,1

        call checkGridBorders2
        cmp ch,1
        jne kingNorthEast

        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je kingNorthEast

        call setSquareColor

    kingNorthEast:
        mov tempRow,ax
        mov tempColumn,di
        sub tempRow,1
        add tempColumn,1

        call checkGridBorders2
        cmp ch,1
        jne kingNorthWest

        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je kingNorthWest

        call setSquareColor

    kingNorthWest:
        mov tempRow,ax
        mov tempColumn,di
        sub tempRow,1
        sub tempColumn,1

        call checkGridBorders2
        cmp ch,1
        jne kingSouthEast

        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je kingSouthEast

        call setSquareColor

    kingSouthEast:
        mov tempRow,ax
        mov tempColumn,di
        add tempRow,1
        add tempColumn,1

        call checkGridBorders2
        cmp ch,1
        jne kingSouthWest

        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je kingSouthWest

        call setSquareColor

    KingSouthWest:
        mov tempRow,ax
        mov tempColumn,di
        add tempRow,1
        sub tempColumn,1

        call checkGridBorders2
        cmp ch,1
        jne returnKing

        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je returnKing

        call setSquareColor
            

    returnKing:
        ret
    ret
kingAvMoves endp



diagonalMoves proc far
    
    mov al,blueEnc  ;setting the color of that position to green
    mov tempColor,al ;storing the new color in tempColor to be passed to the next proc
    mov ax,arrowPointer ;row
    mov di,arrowPointer+2;column
    call getFromPiece ; sets tempFromPiece to the piece in initial location
    
    
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
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je initNorthWest

        call setSquareColor
        cmp notEmptyToPlace,1
        je initNorthWest
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
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je initSouthEast

        call setSquareColor
        cmp notEmptyToPlace,1
        je initSouthEast
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
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je initSouthWest

        call setSquareColor
        cmp notEmptyToPlace,1
        je initSouthWest
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
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je return1
        call setSquareColor
        cmp notEmptyToPlace,1
        je return1
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
    call getFromPiece ; sets tempFromPiece to the piece in initial location

    
    east:    
        add di,1
        mov tempRow,ax
        mov tempColumn,di
        pusha
        call checkGridBorders2
        cmp ch,1
        jne initSouth

        ; Checking if the next position has a piece of the same color
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je initSouth

        call setSquareColor
        cmp notEmptyToPlace,1
        je initSouth
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
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je initNorth

        call setSquareColor
        cmp notEmptyToPlace,1
        je initNorth
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
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je initWest

        call setSquareColor
        cmp notEmptyToPlace,1
        je initWest
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
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je returnAxial
        
        call setSquareColor
        cmp notEmptyToPlace,1
        je returnAxial
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
    
    mov ax,arrowPointer ;row
    mov di,arrowPointer+2;column
    
    knightMove1:
        mov tempRow,ax
        mov tempColumn,di
        add tempRow, 1
        add tempColumn,2

        call checkGridBorders2
        cmp ch,1
        jne knightMove2

        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je knightMove2

        call setSquareColor

    knightMove2:
        mov tempRow,ax
        mov tempColumn,di
        sub tempRow, 1
        add tempColumn,2

        call checkGridBorders2
        cmp ch,1
        jne knightMove3
        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je knightMove3

        call setSquareColor

    knightMove3:
        mov tempRow,ax
        mov tempColumn,di
        add tempRow,2
        add tempColumn, 1

        call checkGridBorders2
        cmp ch,1
        jne knightMove4
        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je knightMove4

        call setSquareColor

    knightMove4:
        mov tempRow,ax
        mov tempColumn,di
        add tempRow,2
        sub tempColumn, 1

        call checkGridBorders2
        cmp ch,1
        jne knightMove5
        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je knightMove5

        call setSquareColor

    knightMove5:
        mov tempRow,ax
        mov tempColumn,di
        sub tempColumn,2
        add tempRow,1

        call checkGridBorders2
        cmp ch,1
        jne knightMove6
        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je knightMove6

        call setSquareColor

    knightMove6:
        mov tempRow,ax
        mov tempColumn,di
        sub tempColumn,2
        sub tempRow,1

        call checkGridBorders2
        cmp ch,1
        jne knightMove7
        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je knightMove7
        call setSquareColor

    knightMove7:
        mov tempRow,ax
        mov tempColumn,di
        sub tempRow,2
        sub tempColumn,1

        call checkGridBorders2
        cmp ch,1
        jne knightMove8
        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je knightMove8

        call setSquareColor

    KnightMove8:
        mov tempRow,ax
        mov tempColumn,di
        sub tempRow,2
        add tempColumn,1

        call checkGridBorders2
        cmp ch,1
        jne returnKnight
        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je returnKnight
        
        call setSquareColor
            
    returnKnight:
        ret

    ret
knightAvMoves endp

blackPawnAvMoves proc
    mov al,blueEnc  ;setting the color of that position to green
    mov tempColor,al ;storing the new color in tempColor to be passed to the next proc

    mov ax,arrowPointer ;row
    mov di,arrowPointer+2;column

    blackPawnMove1:
        mov tempRow,ax
        mov tempColumn,di
        add tempRow,1

        call checkGridBorders2
        cmp ch,1
        jne blackPawnMove3
        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        cmp tempToPiece, emptyEnc
        jne blackPawnMove3

        call isValidPossibleMove
        cmp ch, 0
        je blackPawnMove3

        call setSquareColor

    initBlackPawnMove2: 
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    blackPawnMove2:
        cmp ax, 1 ;Checking if it's the first movement
        jne blackPawnMove3

        mov tempRow,ax
        mov tempColumn,di
        add tempRow,2

        call checkGridBorders2
        cmp ch,1
        jne blackPawnMove3
        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je blackPawnMove3

        call setSquareColor

    blackPawnMove3:
        mov tempRow,ax
        mov tempColumn,di
        add tempRow,1
        add tempColumn, 1

        call checkGridBorders2
        cmp ch,1
        jne blackPawnMove4

        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        cmp tempToPiece, wBishopEnc ;checking if to piece is black or empty (invalid)
        jl blackPawnMove4

        call isValidPossibleMove
        cmp ch, 0
        je blackPawnMove4

        call setSquareColor

    blackPawnMove4:
        mov tempRow,ax
        mov tempColumn,di
        add tempRow,1
        sub tempColumn, 1

        call checkGridBorders2
        cmp ch,1
        jne returnBlackPawn

        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        cmp tempToPiece, wBishopEnc ;checking if to piece is black or empty (invalid)
        jl returnBlackPawn

        call isValidPossibleMove
        cmp ch, 0
        je returnBlackPawn

        call setSquareColor

    returnBlackPawn:
        ret 

    ret
blackPawnAvMoves endp

whitePawnAvMoves proc
    mov al,blueEnc  ;setting the color of that position to green
    mov tempColor,al ;storing the new color in tempColor to be passed to the next proc
    
    mov ax,arrowPointer ;row
    mov di,arrowPointer+2;column

    whitePawnMove1:
        mov tempRow,ax
        mov tempColumn,di
        sub tempRow,1

        call checkGridBorders2
        cmp ch,1
        jne returnWhitePawn
        
        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        cmp tempToPiece, emptyEnc
        jne returnWhitePawn

        call isValidPossibleMove
        cmp ch, 0
        je returnWhitePawn

        call setSquareColor

    initWhitePawnMove2: 
        mov ax,arrowPointer ;row
        mov di,arrowPointer+2;column

    whitePawnMove2:
        cmp ax, 6 ;Checking if it's the first movement
        jne returnWhitePawn

        mov tempRow,ax
        mov tempColumn,di
        sub tempRow,2

        call checkGridBorders2
        cmp ch,1
        jne returnWhitePawn
        ; Checking if the next position has a piece of the same color
        call getFromPiece ; sets tempFromPiece to the piece in initial location
        call getToPiece ; sets tempToPiece to the piece in next location

        call isValidPossibleMove
        cmp ch, 0
        je returnWhitePawn

        call setSquareColor

    returnWhitePawn:
        ret
        
    ret
whitePawnAvMoves endp