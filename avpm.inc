;Available piece moves
bishopAvMoves proc far
    
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
              call setSquareColor
              popa 
              jmp northEast

    initNorthWest: popa
                   mov ax,arrowPointer ;row
                   mov di,arrowPointer+2;column
    northWest:sub ax,1
              sub di,1
              mov tempRow,ax
              mov tempColumn,di
              pusha
              call checkGridBorders2
              cmp ch,1
              jne initSouthEast
              call setSquareColor
              popa 
              jmp northWest


    initSouthEast: popa
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
              call setSquareColor
              popa 
              jmp southEast

     initSouthWest:popa
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
              call setSquareColor
              popa 
              jmp southWest
              

              
  

   return1: popa
            ret
   ret
bishopAvMoves ENDP

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
    
    ret

    bishopAvMovesLabel:call bishopAvMoves
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