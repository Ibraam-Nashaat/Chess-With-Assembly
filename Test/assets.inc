Draw proc far

    call drawGrid
    ;call loopGrid
    mov si,0
    mov di,0
    lea bx,wKnight
    call drawPiece
    mov ah , 0h ;
    int 16h ;
    ret
Draw ENDP

drawGrid proc 
;get the grid data in bx 
    mov cx , 0h ;the column to start drawing at
    mov dx , 0h ;the row to start drawing at
    mov ah ,0ch ;set the draw pixel interrupt mode


    ; loop over the grid pixels colors and put the color in al each  time to draw it
    drawingloop :
    mov si,[bx]
    mov al ,[Bx] ;
    int 10h;
    inc cx;
    inc bx;
    cmp cx ,0c8h;
    JNE drawingloop ;
    mov cx , 0h ;
    inc dx ;
    cmp dx, 0c8h; 0c8h represent 200D  pixel
    JNE drawingloop;

    ret
drawGrid ENDP

drawPiece proc
     ;get the piece data in bx
    mov cx , si;the column to start drawing at
    mov dx , di ;the row to start drawing at
    mov ah ,0ch 

    mov startDrawX,si
    add si,25
    add di,25
    ; loop over the piece pixels colors and put the color in al each  time to draw it
    drawingloop2 :
    mov al ,[Bx] ;
    cmp al,58d
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


loopGrid proc

    lea si,initialGrid
    mov cl,0
    mov dl,0
    mov si,0
    mov di,0

    row: mov al,[bx]
        pusha
        call determinePiece
        popa
        add si,25
        inc bx
        inc cl
        cmp cl,8
        jne row
        
        mov si,0
        add di,25
        mov cl,0
        inc dl
        cmp dl,8
        jne row

    ret
loopGrid ENDP

determinePiece proc
    cmp al,bBishopEnc
    je bBishopPiece

    cmp al,bKingEnc
    je bKingPiece

    

    bBishopPiece: lea bx, bBishop
                  call drawPiece
                  ret

    bKingPiece:   lea bx, bKnight
                  call drawPiece
                  ret            

    ret
determinePiece ENDP

