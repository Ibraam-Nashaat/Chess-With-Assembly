;Available pieces movements utilities
;This file contains the following procedures:
;   1) getClickedPiece 
;   2) checkGridBorders2 

;to get what piece type was clicked
getClickedPiece proc far
    ;get the position of arrowPointer to determine the current position of the piece
    mov ax,arrowPointer ;row 
    mov di,arrowPointer+2;column
    mov tempRow,ax
    mov tempColumn,di

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
    
    ret

    bishopAvMovesLabel:call bishopAvMoves
                       ret

    rookAvailableMovesLabel:call rookAvMoves
                            ret

    queenAvailableMovesLabel:call queenAvMoves
                             ret

    kingAvailableMovesLabel:call kingAvMoves
                            ret
    knightAvailableMovesLabel:call knightAvMoves
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