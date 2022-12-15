;Available pieces movements utilities
;This file contains the following procedures:
;   1) getClickedPiece 
;   2) checkGridBorders2 

getClickedPiece proc far
    mov ax,arrowPointer ;row
    mov di,arrowPointer+2;column
    mov tempRow,ax
    mov tempColumn,di

    call getPiecePosToDraw
    cmp cl,bBishopEnc
    je bishopAvMovesLabel

    cmp cl,wBishopEnc
    je bishopAvMovesLabel

    cmp cl,wRookEnc
    je rookAvailableMovesLabel

    cmp cl,bRookEnc
    je rookAvailableMovesLabel

    cmp cl,wQueenEnc
    je queenAvailableMovesLabel

    cmp cl,bQueenEnc
    je queenAvailableMovesLabel

    cmp cl,wKingEnc
    je kingAvailableMovesLabel

    cmp cl,bKingEnc
    je kingAvailableMovesLabel
    
    ret

    bishopAvMovesLabel:call bishopAvMoves
                       ret

    rookAvailableMovesLabel:call rookAvMoves
                            ret

    queenAvailableMovesLabel:call queenAvMoves
                             ret

    kingAvailableMovesLabel:call kingAvMoves
                            ret

    ret
getClickedPiece endp

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