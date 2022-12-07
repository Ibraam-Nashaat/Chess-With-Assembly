
.MODEL SMALL                     ;Using Small Model Arc
.STACK 100H                      ;Pre order 100H memory STACK
include "./Assets.asm"
DATASEG

CODESEG
main PROC far
mov ax , @data ;
mov ds , ax ;

mov ah,0;
mov al,13h;
int 10h;




MOV bx , OFFSET grid
mov cx , 30h ;
mov dx , 0h ;
mov ah ,0ch ;



drawingloop :
mov si,[bx]
cmp si,'$'
je next
mov al ,[Bx] ;
int 10h;
inc cx;
inc bx;
cmp cx ,0f8h;
JNE drawingloop ;
mov cx , 30h ;
inc dx ;
cmp dx, 0c8h;
JNE drawingloop;


next:

MOV bx , OFFSET wKnight
mov cx , 30h ;
mov dx , 0h ;
mov ah ,0ch ;



drawingloop2 :
mov al ,[Bx] ;
;cmp al,40d
;jg t
cmp al,58d
je t
int 10h;
t:inc cx;
inc bx;
cmp cx ,049h;
JNE drawingloop2 ;
mov cx , 30h ;
inc dx ;
cmp dx, 19h;
JNE drawingloop2;

mov ah , 0h ;
int 16h ;


mov ah , 4ch ;
int 21h;


hlt
main ENDP
End main