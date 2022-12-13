;Available piece moves
bishopAvMoves proc
    mov ax,arrowPointer ;row
    mov di,arrowPointer+2;column
    lea bx,initGrid
    mov al,blueEnc  ;setting the color of that position to green
    mov tempColor,al ;storing the new color in tempColor to be passed to the next proc
    northEast:sub ax,1
              add di,1
              call setSquareColor
              

              


    ret
bishopAvMoves ENDP