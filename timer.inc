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
    loopTimerMatrix:            mov al,[bx]
                                cmp al,0
                                jne decrementTimer
    continueTimerLoopUpdating:   inc bx
                                inc cl
                                cmp cl,64d
                                jne loopTimerMatrix

    popa
    ret
    decrementTimer:dec al
                   mov [bx],al
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