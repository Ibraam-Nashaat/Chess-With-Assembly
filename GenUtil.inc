;General utilities across the program
;This file contains the following procedures:
;   1)getPiecePosToDraw
;   2)getPixelStartPosToDraw
;   3)updateSquareBackgroundAndPiece
;   4)setSquareColor
;   5)setDefaultGridAfterClick
;   6)resetDefGridAfter2ndClick
;   7)checkClickCount
;   8)checkGameRequestSignal

;get the piece pos that we want to redraw
getPiecePosToDraw proc
    ;pieceToRedraw= initPiecePos+(8*row+column)
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


;before calling this procedure you will need to pass
;   1)bx: containing the address of the grid
;   2)tempRow: containig the current row of the cell that you want to recolor
;   3)tempColumn: containing the current column of the cell that you want to recolor
;   4)tempColor: containing the background color encoding of the cell
setSquareColor proc
    ;get the exact position of the cell by 
    ;gridAddress+(8*tempRow+tempColumn)
    pusha
    mov ax,tempRow
    mov di,tempColumn
    lea bx,initGrid
    mov si,8        
    mul si          
    add bx,ax       
    add bx,di       
    mov al,tempColor
    mov [bx],al     ;update the grid background matrix with the new color encoding
    cmp al,blueEnc  
    jne notBlue

    call setDefaultGridAfterClick ;if the color encoding is blue then we will call this proc

    ;reDrawing the grid after the update if the current position is not blue
    notBlue:
        call updateSquareBackgroundAndPiece

    popa
    ret
setSquareColor endp


;This proc aims at recoloring the defGrid with blue cells
;To know the difference between defGrid,initGrid and stdGrid, Refer to the data segment comments.
setDefaultGridAfterClick proc
    ;Pos=defGrid+(8*tempRow+tempColumn)
    pusha
    mov ax,tempRow
    mov di,tempColumn
    lea bx,defGrid
    mov si,8        
    mul si          
    add bx,ax       
    add bx,di       
    mov al,tempColor
    mov [bx],al     ;update the grid background matrix with the new color encoding
    popa
    ret
setDefaultGridAfterClick endp



;reset defGrid back to grey and white by looping over defGrid and stdGrid and comparing
;the color encoding at each single position.
;If it is the same color then we will see the next position, otherwise we would recolor defGrid cell
;with its original grey and white color.
resetDefGridAfter2ndClick proc
    lea bx,defGrid
    lea si,stdGrid
    lea di,initGrid
    mov cx,0

    loopDefGrid:
        mov dl,[bx]
        pusha
        cmp dl,pinkEnc
        je setColorToPink
        cmp dl,[si]
        jne changeColor

    contLoopDefGrid:
        popa
        add si,1
        add bx,1
        add di,1
        inc cx
        cmp cx,64d
        jne loopDefGrid
    ret

    changeColor:
        mov al,[si]
        mov [bx],al ;moving the color encoding of stdGrid to defGrid
        mov bl,greenEnc
        cmp [di],bl
        je setSquareColorToGreen
        mov [di],al ;moving the color encoding of stdGrid to initGrid
        mov tempColor,al
        ;getting the exact position of the cell by
        ;row= cx/8
        ;column=cx%8
 continueChangingColor:       
        mov ax,cx  
        mov cx,8d
        div cx
        mov tempRow,ax
        mov tempColumn,dx
        mov di,dx

        lea bx,initGrid
        call updateSquareBackgroundAndPiece
        jmp contLoopDefGrid
    ret

    setSquareColorToGreen:mov bl,[di]
                          mov tempColor,bl
                          jmp continueChangingColor

    setColorToPink:jmp setSquareColorToGreen

resetDefGridAfter2ndClick endp


;Detect the current count of the Q-click to determine if we would get available moves(1st click)
;or (move or deactivate available moves(2nd click))
checkClickCount proc
    mov al,clickCount
    cmp al,0
    je click1 ;if it is the first click jmp to click1

    ;Otherwise it is the second click
    mov clickCount,0   ;reset the counter back to zero
    call checkFromPosContainsPieceOrNot
    call resetDefGridAfter2ndClick 

    ret
    
    click1:
        inc al
        mov clickCount,al
        call checkIfClickedPieceTimerIsZero
        mov al,canMove
        cmp al,0d
        je pieceTimerIsGreaterThanZero
        call getClickedPiece
        
    pieceTimerIsGreaterThanZero:ret
checkClickCount endp

checkFromPosContainsPieceOrNot proc
    mov ax,clickedPieceRow ;storing the row number
    mov di,clickedPieceCol;storing the column number
    mov tempRow,ax
    mov tempColumn,di
    call getPiecePosToDraw ;get the piece encoding at the clicked position

    ;if there is so piece at the TO position then return
    cmp cl,emptyEnc
    je fromPieceIsEmptyCell

    mov fromPieceEnc,cl
    call checkAvailbleMov

    fromPieceIsEmptyCell:ret ;move isn't available as from position does't contain any piece

    ret
checkFromPosContainsPieceOrNot endp

checkAvailbleMov proc   
    mov ax,arrowPointer ;storing the row number
    mov di,arrowPointer+2;storing the column number
    lea bx,defGrid
    mov si,8
    mul si
    add bx,ax
    add bx,di 
    mov cl,[bx]
    ;check if the clicked TO position is within the available moves or no
    cmp cl,blueEnc
    jne notAvailableMove


    availableMov:
        ;if the move is available then go to its position in initPiecePos and update it with the moving piece encoding
        ;to mimic eating of the piece
        mov ax,arrowPointer
        mov di,arrowPointer+2
        mov tempRow,ax
        mov tempColumn,di
        call getPiecePosToDraw
        call incrementEatenPieces
        mov cl,fromPieceEnc
        call printGameInfo
        call checkIfKingIsEaten
        mov [bx],cl
        call addDelayTimeToMovingPiece
        call markPieceCantMove

        ;update the position of the FROM piece with empty cell in initPiecePos as the piece has moved 
        mov ax,clickedPieceRow ;storing the row number
        mov di,clickedPieceCol;storing the column number
        mov tempRow,ax
        mov tempColumn,di
        call getPiecePosToDraw
        mov cl,emptyEnc
        mov [bx],cl
        call updateSquareBackgroundAndPiece


        lea di,dataToSend
        mov ax,clickedPieceRow
        mov [di],al
        inc di
        mov ax,clickedPieceCol
        mov [di],al
        inc di
        mov ax,arrowPointer
        mov [di],al
        inc di
        mov ax,arrowPointer+2
        mov [di],al
        inc di



        ;update the clicked piece pos with blue Background in order for the next proc to recolor it
        mov ax,clickedPieceRow ;storing the row number
        mov di,clickedPieceCol;storing the column number
        lea bx,defGrid
        mov si,8
        mul si
        add bx,ax
        add bx,di 
        mov cl,blueEnc
        mov [bx],cl
                 
  notAvailableMove:  ret
checkAvailbleMov endp

checkIfKingIsEaten proc
    pusha
    mov al,[bx]
    cmp al,wKingEnc
    je blackWonLabel

    cmp al,bKingEnc
    je whiteWonLabel

    mov al,0
    popa
    ret
 

    blackWonLabel:mov al,1d
                mov exitFlag,al
                lea di,blackWon
                call printWinningMessage
                popa
                ret
    whiteWonLabel:mov al,1d
                  mov exitFlag,al
                  lea di,whiteWon
                  call printWinningMessage
                  popa
    ret
checkIfKingIsEaten endp

printWinningMessage proc
    mov ah,2
    mov dx,0419h
    mov bx,0
    int 10h
    mov ah,0eh
    xor bx,bx
    mov bl,02h
    print:  
        mov al,[di]
        int 10h
        inc di
        mov al,[di]
        cmp al,"$"
        jne print
    ret
printWinningMessage endp

initializeGame proc
    pusha
    lea bx,stdPiecesGrid
    lea di,initPiecePos
    mov cl,0
    loopPiecesMatrix:          
        mov al,[bx]
        mov [di],al
        inc bx
        inc di
        inc cl
        cmp cl,64d
        jne loopPiecesMatrix
                             
    popa
    ret
initializeGame endp

initializeEatenArray proc
    pusha
    lea bx,eatenArray
    mov cl,0
    loopEatenArray:             
        mov al,0
        mov [bx],al
        inc bx
        inc cl
        cmp cl,14d
        jne loopEatenArray
                             
    popa
    ret
initializeEatenArray endp

printGameInfo proc
    pusha
    lea si,eatenArray
    inc si
    mov cl,1

    cmp isBlack, 0
    je printWhiteInfo

    lea di,blackRow1Msg
    mov dx,0019h
    call printMessage

    jmp printPiecesInfo

    printWhiteInfo:
        lea di,whiteRow1Msg
        mov dx,0019h
        call printMessage

    printPiecesInfo:

    lea di,row2Print
    mov dx,0119h
    call printMessage
  

    lea di,row3Print
    mov dx,0219h
    call printMessage

    lea di,row4Print
    mov dx,0319h
    call printMessage
    popa
    ret
printGameInfo endp

printMessage proc

    mov ah,2
    mov bx,0
    int 10h
    mov ah,0eh
    xor bx,bx
    mov bl,02h
    print1:  
        mov al,[di]
        cmp al,"0"
        je changeNumber

    completePrint:
        int 10h
        inc di
        mov al,[di]
        cmp al,"$"
        jne print1
ret


changeNumber:
    cmp cl,wKingEnc
    je incrementSICounter
    cmp cl,bKingEnc
    je incrementSICounter
completeLoop:
    mov al,"0"
    mov ch,[si]
    add al,ch
    inc si
    inc cl
    jmp completePrint

incrementSICounter:
    inc si
    inc cl
    jmp completeLoop
printMessage endp

incrementEatenPieces proc
    pusha
    lea bx,eatenArray
    mov ch,0
    add bx,cx
    mov cl,[bx]
    inc cl
    mov [bx],cl
    popa
    ret
incrementEatenPieces endp

;checkGameRequestSignal proc
;pusha
;    call UART_rec
;    cmp rec_bool, 0
;    ; First Player 
;    je firstPlayerGamePath

;    ; Second Player
;    secondPlayerGamePath:
;        ; Get the byte in serial
;        call receiveByte
;        mov al, VALUE

;        ; Check if it's the right signal from player1
;        cmp al, startGameSignal
;        jne failedStartingGame

;        ifSecondPlayerCanSendGameSignal:
;            call UART_transmit
;            cmp tra_bool, 1 ; If I can send Signal
;            jne ifSecondPlayerCanSendGameSignal

;        sendByte startGameSignal

;    jmp finishedStartingGame

;    firstPlayerGamePath:
;        sendByte startGameSignal

;        ifFirstPlayerReceivedGameSignal:
;            call UART_rec
;            cmp rec_bool, 1 ; If I can send Signal
;            jne ifFirstPlayerReceivedGameSignal

;        ; Get the byte in serial
;        call receiveByte
;        mov al, VALUE
        
;        ; Check if it's the right signal from player1
;        cmp al, startGameSignal
;        je finishedStartingGame

;    failedStartingGame:
;        popa
;        jmp exit ;To Be changed to main menu

;    finishedStartingGame:
;        popa
;ret
;checkGameRequestSignal endp