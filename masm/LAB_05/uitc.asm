; ● усечённое до 8 разрядов значение (аналогично приведению типа int к char в
; языке C) знаковое в 10 с/с.386
.386
EXTRN BIN_NUMBER: byte

PUBLIC output_uint_to_char

SSTK SEGMENT para STACK USE16 'STACK'
    DB 100 dup(0)
SSTK ENDS

SD_OUT2 SEGMENT para USE16 'DATA_OUT1'
    NUM_STR DB 3 dup('0')
    BIN_INDEX DB 15
    MSG_OUT DB 'Num in 8bit signed decimal: ', '$'
SD_OUT2 ENDS

SC SEGMENT para public USE16 'CODE'
	assume CS:SC, DS:SD_OUT2

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
    mov ax, SD_OUT2
    mov ds, ax

    mov ax, 0
    mov cx, 3
    clear_loop:
        lea si, NUM_STR
        mov BYTE PTR [si], '0'
        inc si
        loop clear_loop

    mov BIN_INDEX, 15
    POPA
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
cast_word_to_byte:
    ; mov bx, seg BIN_NUMBER
	; mov es, bx

    mov dx, 0
    mov cx, 8
    cast_loop:
        push cx
        push dx

        lea si, OFFSET es:BIN_NUMBER

        mov bx, 0
        mov bl, BIN_INDEX
        ADD si, bx

        mov bx, 0
        mov bl, es:[BYTE PTR [si]]


        mov ax, 8
        sub ax, cx ; two power
 
        call two_power

        mul bx

        pop dx
        add dx, ax
        
        dec BIN_INDEX
        pop cx
        loop cast_loop
    ret

;in in dx
num_to_str:
    push dx
    mov ax, dx
    

    lea si, OFFSET NUM_STR
    add si, 2

    mov cx, 3
    tr_loop:
        mov dx, 0
        mov bx, 10
        div bx

        add dl, '0'
        mov BYTE PTR [si], dl

        dec si
        loop tr_loop

    pop dx
    ret

print_num_str:
    lea si, OFFSET NUM_STR

    mov cx, 3
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
        inc si
        pop cx
        loop print_loop


    ret


print_sign:
    lea si, OFFSET es:BIN_NUMBER
    add si, 8 ; check signbit

    cmp BYTE PTR es:[si], 0
    je end_ps

    mov dx, 0
    mov dl, '-'
    call print_char

    end_ps:
    ret


output_uint_to_char:
    PUSHA

    mov ax, SD_OUT2
    mov ds, ax

    mov bx, seg BIN_NUMBER
	mov es, bx

    call clear_num
    call cast_word_to_byte ; in dx result

    call num_to_str

    push dx
    mov dx, OFFSET MSG_OUT 
    call print_str
    pop dx

    call print_sign
    call print_num_str
    

    POPA
    ret

SC ENDS
END