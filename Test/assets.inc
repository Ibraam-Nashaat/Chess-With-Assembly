Draw proc far

    call drawGrid
    MOV bx , OFFSET wPawn
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
    mov cx , 0h ;the column to start drawing at
    mov dx , 0h ;the row to start drawing at
    mov ah ,0ch 


    ; loop over the piece pixels colors and put the color in al each  time to draw it
    drawingloop2 :
    mov al ,[Bx] ;
    cmp al,58d
    je t
    int 10h;
    t:inc cx;
    inc bx;
    cmp cx ,19h;
    JNE drawingloop2 ;
    mov cx , 0h ;
    inc dx ;
    cmp dx, 19h;
    JNE drawingloop2;

    ret

drawPiece ENDP




