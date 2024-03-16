; Требуется написать программу из двух модулей. Точку входа 
; разместить в первом, затем передать управление с помощью 
; дальнего перехода во второй, где ввести заглавную букву 
; латинского алфавита, вернуть управление в первый и 
; вывести строчный аналог этой буквы

PUBLIC LETTER
EXTRN scan: far

SSTK SEGMENT para STACK 'STACK'
	db 100 dup(0)
SSTK ENDS

SD SEGMENT para 'DATA'
    OUTMSG  DB 13 
        DB 'Inputed char: '
        DB '$'
    OUTMSG2 DB 13
        DB 'Output char: '
        DB '$'
    DB 1
    LETTER LABEL byte
SD ENDS

SC1 SEGMENT para public 'CODE'
	assume CS:SC1, DS:SD
main:
    mov ax, SD
    mov ds, ax

	call scan

    mov ah, 09h
    mov dx, OFFSET OUTMSG
    int 21h

    mov dl, LETTER
    mov ah, 02h
    int 21h

    mov dl, 10 ;lf
    int 21h

    mov dl, 13 ;cr
    int 21h

    
    mov ah, 09h
    mov dx, OFFSET OUTMSG2
    int 21h

    mov dl, LETTER
    add dl, 20h

    mov ah, 02h
    int 21h

    mov ax, 4c00h
	int 21h
SC1 ENDS
END main
