Draw proc far

    ;call drawGrid
    lea bx,initGrid 
    Mov DrawMode,0
    call loopGrid

    lea bx,initPiecePos
    mov DrawMode,1
    call loopGrid
   

    ret
Draw ENDP


;Draw a specific piece that is passed to it in bx
;The column to start drawing at is passed to the function in si
;The row to start drawing at is passed to the function in di
drawPiece proc
    
    mov cx , si;the column to start drawing at
    mov dx , di ;the row to start drawing at
    mov ah ,0ch ;set the draw pixel interrupt mode

    mov startDrawX,si ;store the start x-position of drawing in startDrawX 
    add si,25    ;store the end X-position of drawing the cube in si
    add di,25    ;store the end Y-positon of drawing the cube in di


    ; loop over the piece pixels colors and put the color in al each  time to draw it
    drawingloop2 :
        mov al ,[Bx] ;
        cmp al,58d ;58d is the pink background that I want to avoid
        je t
        int 10h;
        t:inc cx;
        inc bx;
        cmp cx ,si;
        JNE drawingloop2 ;
    mov cx , startDrawX ;
    inc dx ;
    cmp dx, di;
    JNE drawingloop2;

    ret

drawPiece ENDP



;Loop over the 2D-matrix which is 8*8 to draw their initial positions
loopGrid proc

     ;store the starting position in bx
    mov cl,0   ;set the starting X-position of the 8*8 2D-Matrix of pieces
    mov dl,0   ;set the starting Y-postion of the 8*8 2D-Matrix of pieces

    ;we start drawing from position (0,0) so we need to store the starting position in si and di
    ;to be incremented later by 25d as the piece size is 25*25 pixels
    mov si,0 ;the column to start drawing at
    mov di,0 ;the row to start drawing at

        row: mov al,[bx]    ;st
            pusha
            mov ah,DrawMode
            cmp ah,0
            je gridlabel
            call determinePiece
            jmp  Next
        gridlabel:call determineCubeColor
        Next:popa
            add si,25 ;add 25 to si to jump to the next starting X-position of drawing that would be passed later to drawPiece
            inc bx
            inc cl
            cmp cl,8 ;check whether we have reached the end of a row
            jne row
        mov si,0   ;set the column to start drawing at back to 0 to start the new row
        add di,25 ;add 25 to si to jump to the next starting Y-position of drawing that would be passed later to drawPiece
        mov cl,0   ;set the starting X-position back to 0 to start the new row 
        inc dl
        cmp dl,8    ;check whether we have reached the end of the 2D-matrix
        jne row 

    ret
loopGrid ENDP


;determine which piece to draw now
determinePiece proc
    cmp al,bBishopEnc
    je bBishopPiece

    cmp al,bKingEnc
    je bKingPiece

    cmp al,bKnightEnc
    je bKnightPiece

    cmp al,bPawnEnc
    je bPawnPiece

    cmp al,bQueenEnc
    je bQueenPiece

    cmp al,bRookEnc
    je bRookPiece

    cmp al,wBishopEnc
    je wBishopPiece

    cmp al,wKingEnc
    je wKingPiece

    cmp al,wKnightEnc
    je wKnightPiece

    cmp al,wPawnEnc
    je wPawnPiece

    cmp al,wQueenEnc
    je wQueenPiece

    cmp al,wRookEnc
    je wRookPiece

    ret


    ;set the starting color of each piece then calling drawPiece to draw the whole 25*25 pic
    bBishopPiece: lea bx, bBishop 
                  call drawPiece
                  ret

    bKingPiece:   lea bx, bKing
                  call drawPiece
                  ret  

    bKnightPiece: lea bx,bKnight
                  call drawPiece
                  ret

    bPawnPiece: lea bx,bPawn
                call drawPiece
                ret

    bQueenPiece: lea bx,bQueen
                 call drawPiece
                 ret

    bRookPiece:  lea bx,bRook
                 call drawPiece
                 ret

    wBishopPiece: lea bx,wBishop
                  call drawPiece
                  ret

    wKingPiece: lea bx,wKing
                call drawPiece
                ret

    wKnightPiece:lea bx,wKnight
                call drawPiece
                ret

    wPawnPiece: lea bx,wPawn
                call drawPiece
                ret

    wQueenPiece:lea bx,wQueen
                call drawPiece
                ret

    wRookPiece:lea bx,wRook                      
               call drawPiece
               ret

    ret
determinePiece ENDP

determineCubeColor proc
    cmp al,whiteEnc
    je whiteCube

    cmp al,greyEnc
    je greyCube

    cmp al,greenEnc
    je greenSquare

    cmp al,pinkEnc
    je pinkSquare

    blueCube:mov al,blueColor
             call drawCube

    ret
    whiteCube:mov al,whiteColor
              call drawCube
              ret

    greyCube:mov al,greyColor
             call drawCube
             ret

    greenSquare:mov al,greenColor
                call drawCube
                ret

    pinkSquare:mov al,pinkColor
                call drawCube
                ret

    ret
determineCubeColor Endp


drawCube proc
    mov cx , si;the column to start drawing at
    mov dx , di ;the row to start drawing at
    mov ah ,0ch ;set the draw pixel interrupt mode

    mov startDrawX,si ;store the start x-position of drawing in startDrawX 
    add si,25    ;store the end X-position of drawing the cube in si
    add di,25    ;store the end Y-positon of drawing the cube in di


    ; loop over the cube pixels colors 
    drawingloop3 :
        int 10h;
        inc cx;
        cmp cx ,si;
        JNE drawingloop3 ;
    mov cx , startDrawX ;
    inc dx ;
    cmp dx, di;
    JNE drawingloop3;

    ret
drawCube Endp

