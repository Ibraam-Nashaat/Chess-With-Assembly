;Available piece moves
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
              call setSquareColor
              popa 
              jmp east

    initSouth: popa
                       mov ax,arrowPointer ;row
                       mov di,arrowPointer+2;column
    south:add ax,1
              mov tempRow,ax
              mov tempColumn,di
              pusha
              call checkGridBorders2
              cmp ch,1
              jne initNorth
              call setSquareColor
              popa 
              jmp south


    initNorth: popa
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
              call setSquareColor
              popa 
              jmp north

     initWest:popa
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
              call setSquareColor
              popa 
              jmp west

   returnAxial: popa
            ret
   ret
axialMoves ENDP

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
              call setSquareColor

    initKingSouth: popa
                       mov ax,arrowPointer ;row
                       mov di,arrowPointer+2;column
    kingSouth:add ax,1
              mov tempRow,ax
              mov tempColumn,di
              pusha
              call checkGridBorders2
              cmp ch,1
              jne initKingNorth
              call setSquareColor



    initKingNorth: popa
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
              call setSquareColor


     initKingWest:popa
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
              call setSquareColor
   
    initKingNorthEast:popa
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
              call setSquareColor
         
         

    initKingNorthWest: popa
                   mov ax,arrowPointer ;row
                   mov di,arrowPointer+2;column
    kingNorthWest:sub ax,1
              sub di,1
              mov tempRow,ax
              mov tempColumn,di
              pusha
              call checkGridBorders2
              cmp ch,1
              jne initKingSouthEast
              call setSquareColor



    initKingSouthEast: popa
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
              call setSquareColor


     initKingSouthWest:popa
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
              call setSquareColor
            

   returnKing: popa
                ret
    ret
kingAvMoves endp

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