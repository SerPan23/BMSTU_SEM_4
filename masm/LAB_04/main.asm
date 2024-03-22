; прямоугольная цифровая матрица
; удвоить нечётные элементы в чётных
; строках. Для значений, превысивших 9,
; записать последние цифры

SSTK SEGMENT para STACK 'STACK'
    DB 100 dup(0)
SSTK ENDS

SD SEGMENT para 'DATA'
    MATRIX   DB 81 dup(0)

    M_HEIGHT DB 0
    M_WIDTH  DB 0

    ROW_IND  DB 0
    COL_IND  DB 0

    NEW_EL DB 0
    

    MSG_INP_H  DB 13 
        DB 'Input height: '
        DB '$'
    MSG_INP_W DB 13
        DB 'Input width: '
        DB '$'
    MSG_INP_MAT DB 13
        DB 'Input MATRIX: '
        DB '$'
    MSG_OUT_MAT DB 13
        DB 'Output MATRIX: '
        DB '$'
SD ENDS

SC1 SEGMENT para public 'CODE'
	assume CS:SC1, DS:SD

; data in al
scan_char:
    mov ah, 08h
	int 21h	
	ret

; data in al
scan_char_with_echo:
    mov ah, 01h
	int 21h	
	ret

; data in dl
print_char:
    mov ah, 02h
    int 21h
    ret

; data in dx for examle: mov dx, OFFSET MSG where MSG in DATA
print_str:
    mov ah, 09h
    int 21h
    ret

go_to_new_str:
    mov dl, 10
    call print_char

    mov dl, 13
    call print_char

    ret

; in DS:ROW_IND - row_ind, DS:COL_IND - col_ind
; out dl - el
get_matrix_el:
    mov ax, 0
    mov al, ROW_IND
    mov bx, 0
    mov bl, M_WIDTH
    mul bx ; result in ax
    ADD al, COL_IND

    ; add al, MATRIX
    lea bx, MATRIX
    add bx, ax

    ; mov dl, MATRIX[ax]
    mov dx, 0
    mov dl, BYTE PTR [bx]

    ret

; in DS:ROW_IND - row_ind, DS:COL_IND - col_ind, DS:NEW_EL - new_data
set_matrix_el:
    mov ax, 0
    mov al, ROW_IND
    mov bx, 0
    mov bl, M_WIDTH
    mul bx ; result in ax
    ADD al, COL_IND

    lea bx, MATRIX
    add bx, ax
    ; add al, MATRIX

    ; mov MATRIX[ax], dl
    mov dx, 0
    mov dl, NEW_EL
    
    mov BYTE PTR [bx], dl
    
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

input_in_matrix:
    push cx
    call scan_char_with_echo
    call char_to_num

    mov NEW_EL, al
    call set_matrix_el
    
    pop cx
    ret

input_row:
    push cx
    mov cx, 0
    mov cl, M_WIDTH
    mov COL_IND, 0
    col_loop:
        
        call input_in_matrix

        mov dl, ' '
        call print_char
        
        inc COL_IND
        loop col_loop
    pop cx
    ret

input_matrix:
    mov dx, OFFSET MSG_INP_MAT
    call print_str
    call go_to_new_str

    mov cx, 0

    mov cl, M_HEIGHT
    mov ROW_IND, 0
    row_loop:
        call input_row
        call go_to_new_str

        inc ROW_IND
        loop row_loop

    ret

print_element:
    push cx

    call get_matrix_el
    call num_to_char
    call print_char
    
    pop cx
    ret

print_row:
    push cx
    mov cx, 0
    mov cl, M_WIDTH
    mov COL_IND, 0
    col_loop2:
        
        call print_element

        mov dl, ' '
        call print_char
        
        inc COL_IND
        loop col_loop2
    pop cx
    ret

print_matrix:
    mov dx, OFFSET MSG_OUT_MAT
    call print_str
    call go_to_new_str

    mov cx, 0

    mov cl, M_HEIGHT
    mov ROW_IND, 0
    row_loop2:
        call print_row
        call go_to_new_str

        inc ROW_IND
        loop row_loop2

    ret


modify_element:
    push cx

    mov ax, 0

    call get_matrix_el

    mov al, dl

    mov dx, 2h
    mul dl

    mov dx, 0
    mov dx, 10
    div dl

    mov al, ah

    mov NEW_EL, al
    call set_matrix_el
    
    pop cx
    ret

modify_row:
    push cx

    ; if width <= 1, we don't have odd elements
    mov ax, 0
    mov al, M_WIDTH
    cmp al, 1
    jle end_modify


    mov ax, 0
    mov cx, 0

    mov al, M_WIDTH
    mov dx, 2h
    div dl
    
    mov cl, al

    mov COL_IND, 1

    col_loop3:
        
        call modify_element
        
        add COL_IND, 2
        loop col_loop3

    end_modify:    
    pop cx
    ret

modify_matrix:
    mov cx, 0
    mov ax, 0

    mov al, M_HEIGHT
    mov dx, 2h
    div dl
    add al, ah
    mov cl, al

    mov ROW_IND, 0
    row_loop3:
        call modify_row

        add ROW_IND, 2
        loop row_loop3

    ret


main:
    mov ax, SD
    mov ds, ax

    mov dx, OFFSET MSG_INP_H
    call print_str

    call scan_char_with_echo
    call char_to_num
    mov M_HEIGHT, al

    call go_to_new_str

    mov dx, OFFSET MSG_INP_W
    call print_str

    call scan_char_with_echo
    call char_to_num
    mov M_WIDTH, al

    call go_to_new_str
    call input_matrix

    call modify_matrix

    call print_matrix

    mov ax, 4c00h
	int 21h
SC1 ENDS
END main