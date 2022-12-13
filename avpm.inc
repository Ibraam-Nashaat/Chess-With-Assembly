;Available piece moves
bishopAvMoves proc
    mov ax,arrowPointer ;row
    mov bx,arrowPointer+2;column
    lea si,initGrid
    northEast:sub ax,1
              add bx,1
              


    ret
bishopAvMoves ENDP