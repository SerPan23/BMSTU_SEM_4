; Написать резидентную программу под DOS, которая будет каждую секунду менять
; скорость автоповтора ввода символов в циклическом режиме, от самой медленной до
; самой быстрой. По желанию можно реализовать другой способ взаимодействия с
; устройствами через порты ввода-вывода, но такой, который можно будет
; наглядно продемонстрировать на сдаче лаб. работы.
; Варианты вызова предшествующего обработчика прерывания:
; Командой дальнего вызова подпрограммы CALL в начале обработчика
; прерывания с предварительным сохранением регистра флагов в стеке.
.model tiny

.data 
    INSTALL_MSG db "INSTALL INTERRUPT", 0ah, 0dh, '$'
    UNINSTALL_MSG db "UNINSTALL INTERRUPT", 0ah, 0dh, '$'

    CUR_TIME db 0
    SPEED db 01fh
    OLD_ADDR dd ?

.code
.startup
    jmp install

    IS_INTERRUPT db 1

my_interrupt:
    pushf

    call cs:OLD_ADDR

    ;чтение текущего времени из часов CMOS
    ;СН - значение текущего часа.
    ;CL - значение текущей минуты.
    ;DH - значение текущей секунды.
    mov ah, 02h
    ;1ah - прерывание BIOS для работы с таймером.
    int 1ah             

    cmp dh, CUR_TIME    
    je exit_interrupt  

    mov CUR_TIME, dh    
    dec SPEED     

    test SPEED, 01fh ; логическое И
    jz reset_speed
    jnz set_speed

    reset_speed:
        mov SPEED, 01fh

    set_speed:          
        mov al, 0F3h    ;команда F3h указывает на режим автоповтора

        out 60h, al     ;порт 60h предназначен для работы с клавиатурой 
        
        mov al, SPEED
        out 60h, al     ;устанавливаем скорость автоповтора ввода.

    exit_interrupt:
    iret

install:

    ;считали адрес обработчика прерывания таймера в BIOS   
    ;адрес обработчика сохраняется в регистрах ES и BX
    ;es - адрес сегмента
    ;bx - смещение.
    mov ax, 3508h          
    int 21h

    cmp es:IS_INTERRUPT, 1      
    je uninstall                  

    mov word ptr OLD_ADDR, bx       

    mov word ptr OLD_ADDR + 2, es    

    ;запрос на замену вектора прерывания в таблице векторов прерываний 
    ;на наш обработчик.
    mov ax, 2508h              
    lea dx, my_interrupt
    int 21h   

    mov dx, offset INSTALL_MSG
    mov ah, 09h
    int 21h

    lea dx, install
    int 27h

uninstall:
    mov dx, offset UNINSTALL_MSG
    mov ax, 0             
    mov ah, 09h
    int 21h

    ; возвращаем значения к дефолту
    mov al, 0F3h    

    out 60h, al    

    mov al, 0
    out 60h, al                 

    ; возращаем адрес на исходное прерывание
    mov dx, word ptr es:OLD_ADDR                       
    mov ds, word ptr es:OLD_ADDR + 2
    mov ax, 2508h
    int 21h                  

    ; чистим память (которую можно выделять 48h)
    mov ah, 49h                         
    int 21h

    mov ax, 4C00h
    int 21h

END