; Задание
; Требуется составить программу, которая будет осуществлять:
; ● ввод 16-разрядного числа беззнаковое в 2 с/с;
; ● вывод его в беззнаковое в 16 с/с
; ● усечённое до 8 разрядов значение (аналогично приведению типа int к char в
; языке C) знаковое в 10 с/с
; ● задание на применение команд побитовой обработки: 1-й вариант - степень
; двойки, которой кратно введённое число;
;
; Взаимодействие с пользователем должно строиться на основе меню. Программа
; должна содержать не менее пяти модулей. Главный модуль должен обеспечивать
; вывод меню, а также содержать массив указателей на подпрограммы, выполняющие
; действия, соответствующие пунктам меню. Обработчики действий должны быть
; оформлены в виде подпрограмм, находящихся каждая в отдельном модуле. Вызов
; необходимой функции требуется осуществлять с помощью адресации по массиву
; индексом выбранного пункта меню.
.386

EXTRN input_bin_number: near
; EXTRN output_unsigned_hex: near

EXTRN BIN_NUMBER:byte


SSTK SEGMENT para STACK USE16 'STACK'
    DB 100 dup(0)
SSTK ENDS

SD SEGMENT para USE16 'DATA'
    MSG_INP_H  DB 13 
        DB 'Input height: '
        DB '$'
SD ENDS


SC SEGMENT para public USE16 'CODE'
	assume CS:SC, DS:SD

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

main:
    mov ax, SD
    mov ds, ax

    call input_bin_number

    call go_to_new_str

    ; call output_unsigned_hex

    ; mov bx, seg input_bin_number
	; mov es, bx

    ; call es:input_bin_number

    ; mov bx, seg output_unsigned_hex
	; mov es, bx

    ; call es:output_unsigned_hex


    mov ax, 4c00h
	int 21h

SC ENDS
END main