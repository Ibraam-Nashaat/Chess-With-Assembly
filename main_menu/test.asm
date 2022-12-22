.286
.model huge
.stack 64
.data
chatting_mode db 'To start chatting press F1','$'
game_mode db 'To start the game press F2','$'
end_game db 'To end the program press Esc','$'
msg_name db 'Please enter your name:','$'
msg_startGame db 'Press Enter Key to continue','$'
mybuffer label byte
bufferSize db 15
actualSize db ?
bufferName db 15 dup('$')
.code
include modes.inc
include welcome_window.inc

main PROC far
    mov ax , @data
    mov ds , ax
call welcome_window
call modes
main endp
end main