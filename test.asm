.286
.model Small
.stack 64
.data
Filename db 'grid20.bin', 0h;
filehandle dw ?
chessData db  6400h dup(?);

Filename2 db 'wRookE.bin', 0h;
filehandle2 dw ?
chessData2 db  0190h dup(?);
.code
main PROC far
mov ax , @data ;
mov ds , ax ;

mov ah,0;
mov al,13h;
int 10h;

call OpenFile;
call ReadData;

MOV bx , OFFSET chessData
mov cx , 30h ;
mov dx , 0h ;
mov ah ,0ch ;



drawingloop :
mov al ,[Bx] ;
int 10h;
inc cx;
inc bx;
cmp cx ,0D0h;
JNE drawingloop ;
mov cx , 30h ;
inc dx ;
cmp dx, 0A0h;
JNE drawingloop;

;mov ah , 0h ;
;int 16h ;

call closeFile ;


call OpenFileT;
call ReadDataT;

MOV bx , OFFSET chessData2
mov cx , 30h ;
mov dx , 0h ;
mov ah ,0ch ;



drawingloop2 :
mov al ,[Bx] ;
int 10h;
inc cx;
inc bx;
cmp cx ,044h;
JNE drawingloop2 ;
mov cx , 30h ;
inc dx ;
cmp dx, 14h;
JNE drawingloop2;

mov ah , 0h ;
int 16h ;

call closeFileT ;

mov ah , 4ch ;
int 21h;


hlt
main ENDP

OpenFile proc
mov ah , 3dh ;
mov al ,0h ;
LEA dx,Filename ;
int 21h ;   
mov [filehandle], ax;

RET ;
OpenFile ENDP ;

ReadData proc
mov ah , 3fh ;
mov bx , [filehandle];
mov cx ,6400h;
LEA dx ,chessData;
int 21h;
;mov ah , 3fh;
RET;
ReadData ENDP;


closeFile proc;
mov ah , 3eh;
mov bx , [filehandle];
int 21h;
RET ;
closeFile ENDP;

OpenFileT proc
mov ah , 3dh ;
mov al ,0h ;
LEA dx,Filename2 ;
int 21h ;   
mov [filehandle2], ax;

RET ;
OpenFileT ENDP ;

ReadDataT proc
mov ah , 3fh ;
mov bx , [filehandle2];
mov cx ,0190h;
LEA dx ,chessData2;
int 21h;
;mov ah , 3fh;
RET;
ReadDataT ENDP;


closeFileT proc;
mov ah , 3eh;
mov bx , [filehandle2];
int 21h;
RET ;
closeFileT ENDP;

End main