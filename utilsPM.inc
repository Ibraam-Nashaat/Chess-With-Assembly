;Available pieces movements utilities
;This file contains the following procedures:
;   1) getClickedPiece 
;   2) checkGridBorders2 
;   3) isValidPossibleMove
;   4) getPieceInPos
;   5) getFromPiece
;   6) getToPiece

;to get what piece type was clicked
getClickedPiece proc far
    ;get the position of arrowPointer to determine the current position of the piece
    mov ax,arrowPointer ;row 
    mov di,arrowPointer+2;column
    mov tempRow,ax
    mov tempColumn,di
    mov clickedPieceRow,ax
    mov clickedPieceCol,di

    call getPiecePosToDraw ;to get the piece encoding in cl

    ;The clicked piece is Bishop
    cmp cl,bBishopEnc
    je bishopAvMovesLabel

    cmp cl,wBishopEnc
    je bishopAvMovesLabel

    ;The clicked piece is Rook
    cmp cl,wRookEnc
    je rookAvailableMovesLabel

    cmp cl,bRookEnc
    je rookAvailableMovesLabel

    ;The clicked piece is Queen
    cmp cl,wQueenEnc
    je queenAvailableMovesLabel

    cmp cl,bQueenEnc
    je queenAvailableMovesLabel

    ;The clicked piece is King
    cmp cl,wKingEnc
    je kingAvailableMovesLabel

    cmp cl,bKingEnc
    je kingAvailableMovesLabel

    ;The clicked piece is knight
    cmp cl, wKnightEnc
    je knightAvailableMovesLabel

    cmp cl, bKnightEnc
    je knightAvailableMovesLabel

    ;The clicked piece is pawn
    cmp cl, bPawnEnc
    je blackPawnAvailableMovesLabel

    cmp cl, wPawnEnc
    je whitePawnAvailableMovesLabel

    ;The user clicked on an empty place
    cmp cl, emptyEnc
    je resetClickCountLabel
    
    ret

    bishopAvMovesLabel:
        call bishopAvMoves
        ret

    rookAvailableMovesLabel:
        call rookAvMoves
        ret

    queenAvailableMovesLabel:
        call queenAvMoves
        ret

    kingAvailableMovesLabel:
        call kingAvMoves
        ret
                            
    knightAvailableMovesLabel:
        call knightAvMoves
        ret

    blackPawnAvailableMovesLabel:
        call blackPawnAvMoves
        ret

    whitePawnAvailableMovesLabel:
        call whitePawnAvMoves
        ret

    resetClickCountLabel:
        mov clickCount, 0
        ret

    ret
getClickedPiece endp

;Check if the current position that we want to color is out of grid range
checkGridBorders2 proc
    cmp tempRow,7d
    jg outOfRange2 ;if it is greater than 7 then it is out of range

    cmp tempRow,0
    jl outOfRange2 ;if it is lower than 0 then it is out of range

    cmp tempColumn,7d
    jg outOfRange2 ;if it is greater than 7 then it is out of range

    cmp tempColumn,0
    jl outOfRange2 ;if it is lower than 0 then it is out of range
    
    mov ch,1       ;set a flag indicating that it is within the range
    ret

    outOfRange2:mov ch,0 ;set a flag indicating that it is out of Range
    ret
checkGridBorders2 Endp

isValidPossibleMove proc
    mov notEmptyToPlace,0

    cmp tempFromPiece, wBishopEnc ;checking if from piece is black
    jl fromPieceIsBlack

    fromPieceIsWhite:
        cmp isBlack, 1
        je secondPieceHasSameColor ;Invalid

        cmp tempToPiece, emptyEnc
        je emptySquare

        cmp tempToPiece, wBishopEnc ;checking if to piece is black
        jl secondPieceNotSameColor

        jmp secondPieceHasSameColor

    fromPieceIsBlack:
        cmp isBlack, 0
        je secondPieceHasSameColor ;Invalid 

        cmp tempToPiece, emptyEnc
        je emptySquare

        cmp tempToPiece, bRookEnc ;checking if to piece is white
        jg secondPieceNotSameColor

    secondPieceHasSameColor:
        mov ch, 0 ;set a flag indicating that the second piece has the same color
        mov notEmptyToPlace,1
        ret

    secondPieceNotSameColor:
        mov ch, 1 ;set a flag indicating that the second piece does not have the same color
        mov notEmptyToPlace,1
        ret

    emptySquare:
        mov ch,1
        ret

isValidPossibleMove endp

; From piece is located in (ax, di)
getPieceInPos proc
    lea bx,initPiecePos
    mov si,8
    mul si
    add bx,ax
    add bx,di 
    mov cl, [bx]
    ret
getPieceInPos endp

getFromPiece proc
    pusha
    lea bx,initPiecePos
    mov si,8
    mul si
    add bx,ax
    add bx,di 
    mov cl, [bx]
    mov tempFromPiece, cl
    popa
    ret
getFromPiece endp

getToPiece proc
    pusha
    mov ax,tempRow
    mov di,tempColumn
    lea bx,initPiecePos
    mov si,8
    mul si
    add bx,ax
    add bx,di 
    mov cl, [bx]
    mov tempToPiece, cl
    popa
    ret
getToPiece endp