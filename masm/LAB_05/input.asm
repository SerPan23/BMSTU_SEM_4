; ● ввод 16-разрядного числа беззнаковое в 2 с/с;
.386
PUBLIC input_bin_number
PUBLIC BIN_NUMBER

SSTK SEGMENT para STACK USE16 'STACK'
    DB 100 dup(0)
SSTK ENDS

SD_INP SEGMENT para USE16 'DATA_INPUT'
    BIN_NUMBER_STR LABEL BYTE
    BIN_STR_SIZE DB 17
    BIN_STR_READED DB 0
    BIN_STR_DATA DB 16 dup('0')
    BIN_END DB '$'

    BIN_NUMBER DB 16 dup(0)
    

    MSG_INP_BN  DB 13 
        DB 'Input bin number: '
        DB '$'
SD_INP ENDS

SC SEGMENT para public USE16 'CODE'
	assume CS:SC, DS:SD_INP

print_char:
    mov ah, 02h
    int 21h
    ret

go_to_new_str:
    mov dl, 10
    call print_char

    mov dl, 13
    call print_char

    ret

; data in dx for examle: mov dx, OFFSET MSG where MSG in DATA
print_str:
    push ax
    mov ah, 09h
    int 21h
    pop ax
    ret

; in - dl
; out - dl
num_to_char:
    ADD dl, 30h
    ret

; in - al
; out - al
char_to_num:
    SUB al, 30h
    ret

clear_data:
    ; PUSHA

    ; mov ax, SD_INP
    ; mov ds, ax
    push ax
    push cx

    ; mov ax, 0
    ; mov al, BIN_STR_SIZE
    ; DEC ax
    lea si, BIN_STR_DATA
    lea bx, BIN_NUMBER

    mov cx, 0
    mov cl, 16
    clear_loop:
        mov BYTE PTR [si], '0'
        mov BYTE PTR [bx], 0
        inc si
        inc bx
        loop clear_loop

    mov BIN_STR_READED, 0
    mov BIN_END, '$'

    pop cx
    pop ax
    ; POPA
    ret

input_str:
    ; PUSHA
    ; mov ax, SD_INP
    ; mov ds, ax

    call clear_data

    mov dx, offset BIN_NUMBER_STR
    mov ax, 0
    mov ah, 0ah
    int 21h    

    mov BIN_END, '$'

    ; POPA
    ret

; str: 1111 1010 0000 0000
; read: 7
; cx: read - 1
; ind: start init read and dec in iter
; str_ind: start_str + (read - ind) | 6   init start_str and inc in iter
; num_ind: start_num + (16 - ind)   | 15  init start_num + (16 - ind) and inc in iter
; num: 0000 0000 0111 1101

bin_str_to_num:
    cmp BIN_STR_READED, 0
    je exit_convert
    
    ; init str_ind
    lea si, BIN_STR_DATA

    ; init start_num
    mov bx, 0
    lea bx, BIN_NUMBER
    add bx, 16
    sub bl, BIN_STR_READED

    mov cx, 0
    mov cl, BIN_STR_READED
    ; DEC cx

    convert_loop:
        mov ax, 0
        mov al, BYTE PTR [si]
        call char_to_num
        mov BYTE PTR [bx], al

        inc si
        inc bx
        loop convert_loop

    exit_convert:
    ret

input_bin_number:
    PUSHA
    mov ax, SD_INP
    mov ds, ax

    call clear_data

    mov dx, OFFSET MSG_INP_BN
    call print_str

    call input_str
    
    call go_to_new_str

    call bin_str_to_num

    POPA
    ret


SC ENDS
END