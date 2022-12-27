checkTimer proc
    pusha
        ;GET SYSTEM TIME.
        mov  ah, 2ch
        int  21h ;RETURN SECONDS IN DH.
        ;CHECK IF ONE SECOND HAS PASSED. 
        cmp  dh, seconds
        je   no_change
        ;IF NO JUMP, ONE SECOND HAS PASSED. VERY IMPORTANT : PRESERVE SECONDS TO
        ;USE THEM TO COMPARE WITH NEXT SECONDS. THIS IS HOW WE KNOW ONE SECOND
        ;HAS PASSED.
        mov  seconds, dh
        call updateTimerMatrix
        
         
   no_change:   popa
                ret
checkTimer endp

updateTimerMatrix proc 
    pusha
    lea bx,timer
    mov cl,0
    mov si,0 ;row
    mov di,0 ;column

        loopTimerMatrix:            mov al,[bx]
                                    cmp al,0
                                    jne decrementTimer
         continueTimerLoopUpdating: inc bx
                                    inc di
                                    inc cl
                                    cmp di,8d
                                    jne loopTimerMatrix
                                mov di,0
                                inc si
                                cmp si,8d
                                jne loopTimerMatrix

    popa
    ret
    decrementTimer:dec al
                   mov [bx],al
                   cmp al,0
                   je markPieceAsItCanMoveLabel
                   jmp continueTimerLoopUpdating

    markPieceAsItCanMoveLabel:call markPieceAsItCanMove
                              jmp continueTimerLoopUpdating
updateTimerMatrix endp


addDelayTimeToMovingPiece proc
    pusha
    call getPiecePosTimer
    mov [bx],3d
    popa
    ret
addDelayTimeToMovingPiece endp

checkIfClickedPieceTimerIsZero proc
    pusha
    call getPiecePosTimer
    mov bl,[bx]
    cmp bl,0d
    jne canNotMove
    mov canMove,1
    popa
    ret
    canNotMove: mov canMove,0
                popa
                ret
checkIfClickedPieceTimerIsZero endp

getPiecePosTimer proc
    mov ax,arrowPointer
    mov di,arrowPointer+2
    lea bx,timer
    mov si,8
    mul si
    add bx,ax
    add bx,di 
    ret
getPiecePosTimer endp

markPieceCantMove proc
pusha
    mov ax,tempRow
    mov di,tempColumn
    lea bx,defGrid
    mov si,8        
    mul si          
    add bx,ax       
    add bx,di       
    mov al,pinkEnc
    mov [bx],al 
popa
ret
markPieceCantMove endp

markPieceAsItCanMove proc
    pusha
    mov tempRow,si
    mov tempColumn,di
    lea si,stdGrid
    lea di,defGrid
    lea bx,initGrid


    mov ch,0
    add si,cx
    add di,cx
    add bx,cx
    mov al,[si]
    mov [di],al

    mov cl,greenEnc
    cmp [bx],cl
    je return9
    mov [bx],al
    mov tempColor,al


    lea bx,initGrid
    call updateSquareBackgroundAndPiece

    return9:
    popa
    ret
markPieceAsItCanMove endp