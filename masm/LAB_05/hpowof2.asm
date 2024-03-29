; ● задание на применение команд побитовой обработки: 1-й вариант - степень
; двойки, которой кратно введённое число;
.386
EXTRN BIN_NUMBER: byte

PUBLIC output_highest_power_of_2

SSTK SEGMENT para STACK USE16 'STACK'
    DB 100 dup(0)
SSTK ENDS

SD_OUT3 SEGMENT para USE16 'DATA_OUT1'
    BIN_INDEX DB 15
SD_OUT3 ENDS

SC SEGMENT para public USE16 'CODE'
	assume CS:SC, DS:SD_OUT3

; data in dl
print_char:
    push ax

    mov ax, 0
    mov ah, 02h
    int 21h
    
    pop ax
    ret

; in - dl
; out - dl
num_to_char:
    ADD dl, 30h
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

; out in dx
bin_to_num:
    ; mov bx, seg BIN_NUMBER
	; mov es, bx

    mov dx, 0
    mov cx, 16
    cast_loop:
        push cx
        push dx

        lea si, OFFSET es:BIN_NUMBER

        mov bx, 0
        mov bl, BIN_INDEX
        ADD si, bx

        mov bx, 0
        mov bl, es:[BYTE PTR [si]]


        mov ax, 16
        sub ax, cx ; two power
 
        call two_power

        mul bx

        pop dx
        add dx, ax
        
        dec BIN_INDEX
        pop cx
        loop cast_loop
    ret

; in - dx
; out - ax
; n & (~(n - 1))
find_power:
    mov ax, dx

    mov cx, ax
    dec cx
    not cx

    and ax, cx

    ret

; in - ax
; out - bx
find_power_num:
    BSF bx, ax
    ret

output_highest_power_of_2:
    PUSHA

    mov ax, SD_OUT3
    mov ds, ax

    mov bx, seg BIN_NUMBER
	mov es, bx

    call bin_to_num ; out dx
    call find_power ; out ax
    call find_power_num ; out bx

    mov dl, al
    call num_to_char
    call print_char

    mov dl, ' '
    call print_char
     mov dl, '('
    call print_char

    mov dl, bl
    call num_to_char
    call print_char

    mov dl, ')'
    call print_char

    POPA
    ret

SC ENDS
END