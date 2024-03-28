; ● ввод 16-разрядного числа беззнаковое в 2 с/с;
.386
PUBLIC BIN_NUMBER_DATA
PUBLIC input_str

SSTK SEGMENT USE16 para STACK 'STACK'
    DB 100 dup(0)
SSTK ENDS

SD_INP SEGMENT USE16 para 'DATA_INPUT'
    BIN_NUMBER_STR LABEL BYTE
    BIN_NUMBER_SIZE DB 16
    BIN_NUMBER_READED DB 0
    BIN_NUMBER_DATA DB 16 dup('0')
    BIN_END DB '$'
    ; BIN_NUMBER_STR LABEL BYTE
    ; BIN_NUMBER_SIZE DB 16
    ; BIN_NUMBER_READED DB 16
    ; BIN_NUMBER_DATA DB '0000000000011010'
    ; BIN_END DB '$'

    MSG_INP_BN  DB 13 
        DB 'Input bin number: '
        DB '$'
SD_INP ENDS

SCI SEGMENT USE16 para public 'CODE'
	assume CS:SCI, DS:SD_INP

clear_data:
    PUSHA

    mov ax, SD_INP
    mov ds, ax

    mov ax, 0
    mov al, BIN_NUMBER_SIZE
    DEC ax

    mov cx, 0
    mov cl, BIN_NUMBER_SIZE
    clear_loop:
        lea si, BIN_NUMBER_DATA
        add si, ax
        mov BYTE PTR [si], 0
        DEC ax
        loop clear_loop

    POPA
    ret

input_str:
    PUSHA
    mov ax, SD_INP
    mov ds, ax

    call clear_data

    mov dx, offset BIN_NUMBER_STR
    mov ax, 0
    mov ah, 0ah
    int 21h  

    mov dx, offset BIN_NUMBER_STR
    mov ax, 0
    mov ah, 9
    int 21h      

    POPA
    retf


SCI ENDS
END input_str