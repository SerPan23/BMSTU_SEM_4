; ● вывод его в беззнаковое в 16 с/с
.386

EXTRN BIN_NUMBER_DATA: byte

PUBLIC output_unsigned_hex

SSTK SEGMENT USE16 para STACK 'STACK'
    DB 100 dup(0)
SSTK ENDS

SD_OUT1 SEGMENT USE16 para 'DATA_OUT1'
    ALPHABET DB 'A'
        DB 'B'
        DB 'C'
        DB 'D'
        DB 'E'
        DB 'F'

    HEX_NUM_16 DB 4 dup('0')

    BIN_INDEX DB 15

SD_OUT1 ENDS

SCO1 SEGMENT USE16 para public 'CODE'
	assume CS:SCO1, DS:SD_OUT1

clear_num:
    PUSHA
    mov ax, SD_OUT1
    mov ds, ax

    mov ax, 3
    mov cx, 4
    clear_loop:
        lea si, HEX_NUM_16
        add si, ax
        mov BYTE PTR [si], '0'
        DEC ax
        loop clear_loop

    mov BIN_INDEX, 15
    POPA
    ret

; in ax
; out ax
transform_num_to_hex_digit:
    PUSHA

    mov ax, SD_OUT1
    mov ds, ax

    cmp ax, 9
    jbe transform_num_to_char

    SUB ax, 10

    lea si, OFFSET ALPHABET
    ADD si, ax

    mov ax, 0
    mov al, BYTE PTR [si]
    
    jmp end_tr

    transform_num_to_char:
        ADD ax, '0'

    end_tr:
        POPA
    ret

; pow - ax
; out - ax
two_power:
    push cx
    push dx
    mov cx, ax
    mov ax, 1
    
    cmp cx, 0
    je end_power

    mov dx, 2
    
    power_loop:
        mul dx
        loop power_loop


    end_power:
    pop cx
    pop dx
    ret

; in tetrad num - ax
; out - ax
cast_one_digit:
    push cx
    push ax
    push bx

    mov ax, SD_OUT1
    mov ds, ax

    mov bx, seg BIN_NUMBER_DATA
	mov es, bx
    
    mov cx, 4
    mov dx, 0
    tet_loop:
        lea si, OFFSET es:BIN_NUMBER_DATA

        mov bx, 0
        mov bl, BIN_INDEX
        ADD si, bx

        mov bx, 0
        mov bl, BYTE PTR [si]


        mov ax, 4
        sub ax, cx ; two power

        call two_power

        mul bx

        add dx, ax
        
        dec BIN_INDEX
        loop tet_loop


    mov ax, dx
    call transform_num_to_hex_digit
    mov dx, ax

    pop ax
    
    lea si, OFFSET HEX_NUM_16
    dec ax
    add si, ax
    mov BYTE PTR [si], dl

    pop cx
    pop bx
    ret


; take 4 digits and mul each of them to next two_power
; 00011010 = (0001)(1010) = (0*2^3 + 0*2^2 + 0*2^1 + 1*2^0)(1*2^3 + 0*2^2 + 1*2^1 + 0*2^0) 
; = (0+0+0+1)(8+0+2+0) = (1)(10) = 1A in (16)

cast_num_to_unsigned_hex:
    PUSHA
    mov ax, SD_OUT1
    mov ds, ax


    mov cx, 4
    cast_loop:
        mov ax, cx

        call cast_one_digit

        loop cast_loop

    

    POPA
    ret

; data in dl
print_char:
    mov ah, 02h
    int 21h
    ret

output_unsigned_hex:
    PUSHA

    mov ax, SD_OUT1
    mov ds, ax

    call clear_num
    call cast_num_to_unsigned_hex

    mov cx, 4
    mov ax, 0
    print_loop:
        lea si, HEX_NUM_16
        add si, ax
        mov dx, 0
        mov dl, BYTE PTR [si]

        call print_char
        loop print_loop

    POPA
    retf

SCO1 ENDS
END