;This file contains all procedures related to the arrow Pointer
;This file contains the following procedures:
;   1)moveArrow
;   2)redrawNewArrowPos
;   3)checkGridBorders
;   4)redrawOldArrowPos

moveArrow proc
    ;check loop is for getting the key pressed without waiting for it
    CHECK:  
        call checkTimer
        call handleGameSendAndReceive
        mov al,exitFlag
        cmp al,1d
        je exitGame
        mov al,exitFlagFromOtherSide
        cmp al,1d
        je exitBasedOnOtherSide
        mov ah,1 
        int 16h
        jz CHECK 

    ;Once we detect that the user pressed a key we need to consume it from the buffer
    ;so we will use the following interrupt
    mov ah,0
    int 16h 

    cmp ah,48h ;compare the scancode of the the key that we got to that of the Up-key
    je moveUp

    cmp ah,50h ;compare the scancode of the the key that we got to that of the Down-key
    je moveDown

    cmp ah,4dh  ;compare the scancode of the the key that we got to that of the Right-key
    je moveRight

    cmp ah,4bh ;compare the scancode of the the key that we got to that of the Left-key
    je tempMoveLeft

    cmp ah,0fh ;compare the scancode of the key that we got to that of the Tab-key
    je tempClick
    cmp ah,3Eh
    je exitGame

    mov VALUE,al
    call printTransmitterChar
    ret
    exitGame:
            mov al,1d
            mov exitFlag,al
            mov dataToSend,"#"
            call handleGameSendAndReceive
            ret
    exitBasedOnOtherSide:mov al,1d
                         mov exitFlag,al
                        ret
    moveUp:
        mov ax,arrowPointer 
        dec ax               ;To move the arrowPointer up we will need to dec the row number
        mov tempNewArrowptr,ax ;We will store it temporarily because we will need it later
        call checkGridBorders ;check that the new position of arrowPointer is within the grid range
        cmp ch,0              
        je tempReturn            ;if the new arrowPosition is out of range we won't do anything so we would return
        call redrawOldArrowPos;To redraw the old ArrowPosition with its default color in the grid
        mov ax,tempNewArrowptr
        mov arrowPointer,ax  ;update the arrowPointer position with the new position
        jmp tempUpdateGrid      ;jmp to updateGrid reDraw the grid and the pieces
    moveDown:
        mov ax,arrowPointer
        inc ax
        mov tempNewArrowptr,ax
        call checkGridBorders
        cmp ch,0
        je tempReturn
        call redrawOldArrowPos
        mov ax,tempNewArrowptr
        mov arrowPointer,ax
        jmp tempUpdateGrid
                    tempReturn:jmp return
                    tempMoveLeft:jmp moveLeft

    moveRight: 
        mov ax,arrowPointer+2
        inc ax
        mov tempNewArrowptr,ax
        call checkGridBorders
        cmp ch,0
        je tempReturn
        call redrawOldArrowPos
        mov ax,tempNewArrowptr
        mov arrowPointer+2,ax
        jmp tempUpdateGrid
        tempClick:jmp click
            tempUpdateGrid:jmp updateGrid

    moveLeft: 
        mov ax,arrowPointer+2
        dec ax
        mov tempNewArrowptr,ax
        call checkGridBorders
        cmp ch,0
        je return
        call redrawOldArrowPos
        mov ax,tempNewArrowptr
        mov arrowPointer+2,ax
        jmp updateGrid
    click:
        call checkClickCount
        cmp exitFlag,1
        je lastCall
        ret
        lastCall:call handleGameSendAndReceive
                mov al,1d
                 mov exitFlag,al
                mov dataToSend,"#"
                call handleGameSendAndReceive
    updateGrid: 
        call redrawNewArrowPos
    return:  ret

moveArrow ENDP

;Update the grid matrix (initGrid) which contains the colors of the square background
;with the color of the arrowPointer at the new position
;The following proc aims at getting the position of the arrowPointer in initGrid matrix
;by this equation  initGrid+(row*8+column)
redrawNewArrowPos proc
    mov al,greenEnc  ;setting the color of that position to green
    mov tempColor,al ;storing the new color in tempColor to be passed to the next proc
    mov ax,arrowPointer ;get the row index of the arrowPointer
    mov di,arrowPointer+2 ;get the column index  of the arrowPointer
    mov tempRow,ax ;storing the row number
    mov tempColumn,di
    lea bx,initGrid ;store the address of initGrid
    call setSquareColor
    ret
redrawNewArrowPos endp


;check that the new ArrowPosition is within the Grid Range
checkGridBorders proc
    cmp ax,7d
    jg outOfRange ;if it is greater than 7 then it is out of range

    cmp ax,0
    jl outOfRange ;if it is lower than 0 then it is out of range
    
    mov ch,1       ;set a flag indicating that it is within the range
    ret

    outOfRange:mov ch,0 ;set a flag indicating that it is out of Range
    ret
checkGridBorders Endp

;recoloring old Arrow position with the original color of the backgroud (grey and white)
;by comparing DefGrid 
;with initGrid (which contains the colors of the background that we draw)
redrawOldArrowPos proc
    ;get the aimed position that we want to compare 
    ;by DefGrid+(row*8+column)
    mov ax,arrowPointer ;storing the row number
    mov di,arrowPointer+2 ;storing the column number
    lea bx,DefGrid
    mov si,8
    mul si
    add bx,ax
    add bx,di 
    mov ch,[bx] ;store the color that we want
    
    ;initGrid+(row*8+column)
    mov ax,arrowPointer
    mov di,arrowPointer+2
    mov tempRow,ax ;storing the row number
    mov tempColumn,di
    lea bx,initGrid
    mov si,8
    mul si
    add bx,ax
    add bx,di 
    mov [bx],ch ;replace the current color of old arrowPosition with its original default color stored in ch
                ;that we got from DefGrid

    mov tempColor,ch
    call updateSquareBackgroundAndPiece
    
    ret
redrawOldArrowPos endp 
