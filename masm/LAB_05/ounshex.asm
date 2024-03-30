; ● вывод его в беззнаковое в 16 с/с
.386

EXTRN BIN_NUMBER: byte

PUBLIC output_unsigned_hex

SSTK SEGMENT para STACK USE16 'STACK'
    DB 100 dup(0)
SSTK ENDS

SD_OUT1 SEGMENT para USE16 'DATA_OUT1'
    ALPHABET DB 'A'
        DB 'B'
        DB 'C'
        DB 'D'
        DB 'E'
        DB 'F'

    HEX_NUM_16 DB 4 dup('0')

    BIN_INDEX DB 15

    MSG_OUT DB 'Num in unsigned hex: ', '$'
SD_OUT1 ENDS

SC SEGMENT para public USE16 'CODE'
	assume CS:SC, DS:SD_OUT1

; data in dl
print_char:
    push ax

    mov ax, 0
    mov ah, 02h
    int 21h

    pop ax
    ret

; data in dx for examle: mov dx, OFFSET MSG where MSG in DATA
print_str:
    push ax
    mov ah, 09h
    int 21h
    pop ax
    ret

clear_num:
    PUSHA
    mov ax, SD_OUT1
    mov ds, ax

    lea si, HEX_NUM_16

    mov cx, 4
    clear_loop:
        mov BYTE PTR [si], '0'
        inc si
        loop clear_loop

    mov BIN_INDEX, 15
    POPA
    ret

; in ax
; out ax
transform_num_to_hex_digit:
    ; PUSHA

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
        ; POPA
    ret

; pow - ax
; out - ax
two_power:
    push cx
    push dx
    mov cx, ax
    mov ax, 0
    mov al, 1
    
    cmp cx, 0
    je end_power

    mov dx, 0
    mov dl, 2
    
    power_loop:
        mul dl
        loop power_loop


    end_power:
    pop dx
    pop cx
    ret

; in tetrad num - ax
; out - ax
cast_one_digit:
    push cx
    push bx
    push ax

    mov bx, seg BIN_NUMBER
	mov es, bx
    
    mov cx, 4
    mov dx, 0
    tet_loop:
        push cx
        push dx
        lea si, OFFSET es:BIN_NUMBER

        mov bx, 0
        mov bl, BIN_INDEX
        ADD si, bx

        mov bx, 0
        mov bl, es:[BYTE PTR [si]]


        mov ax, 4
        sub ax, cx ; two power
 
        call two_power

        mul bx

        pop dx
        add dx, ax
        
        dec BIN_INDEX
        pop cx
        loop tet_loop


    mov ax, dx
    call transform_num_to_hex_digit
    mov dx, ax

    pop ax
    
    lea si, OFFSET HEX_NUM_16
    dec ax
    add si, ax
    mov BYTE PTR [si], dl

    pop bx
    pop cx
    ret


; take 4 digits and mul each of them to next two_power
; 00011010 = (0001)(1010) = (0*2^3 + 0*2^2 + 0*2^1 + 1*2^0)(1*2^3 + 0*2^2 + 1*2^1 + 0*2^0) 
; = (0+0+0+1)(8+0+2+0) = (1)(10) = 1A in (16)

cast_num_to_unsigned_hex:
    mov cx, 4
    cast_loop:
        mov ax, cx

        call cast_one_digit

        loop cast_loop
    ret

print_hex_str:
    lea si, HEX_NUM_16

    mov cx, 4
    mov ax, 0 ; flag
    print_loop:
        push cx

        cmp ax, 0
        je check_p
        jne print_p
        
        check_p:
        cmp BYTE PTR [si], '0'
        je loop_end
        mov ax, 1

        print_p:
        mov dx, 0
        mov dl, BYTE PTR [si]
        call print_char

        loop_end:
        INC si
        pop cx
        loop print_loop
    ret

output_unsigned_hex:
    PUSHA

    mov ax, SD_OUT1
    mov ds, ax

    call clear_num
    call cast_num_to_unsigned_hex

    push dx
    mov dx, OFFSET MSG_OUT 
    call print_str
    pop dx

    call print_hex_str

    POPA
    ret

SC ENDS
END