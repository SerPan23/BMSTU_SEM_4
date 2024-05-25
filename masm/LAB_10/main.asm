bits 64
global main

global ans

%define GTK_WIN_POS_CENTER 1
%define GTK_WIN_WIDTH 700
%define GTK_WIN_HEIGHT 450

extern exit
extern gtk_init
extern gtk_main
extern g_object_set
extern gtk_main_quit
extern gtk_window_new
extern gtk_widget_show
extern g_signal_connect
extern gtk_window_set_title
extern g_signal_connect_data
extern gtk_window_set_position
extern gtk_settings_get_default
extern gtk_widget_set_size_request
extern gtk_window_set_default_size

extern gtk_widget_show_all


extern gtk_layout_new
extern gtk_layout_put

extern gtk_label_new
extern gtk_label_set_text

extern gtk_container_add

extern gtk_entry_new
extern gtk_entry_set_placeholder_text
extern gtk_entry_set_text
extern gtk_entry_get_text

extern gtk_button_new_with_label


extern g_ascii_strtod
extern g_ascii_dtostr

extern find_func_root
; extern num_to_str
extern str_to_double
extern str_func_root

section .bss
    window: resq 1
    layout: resq 1
    entry_1: resq 1
    entry_2: resq 1
    entry_3: resq 1
    calc_btn: resq 1
    result_label_text: resq 1
    result_label: resq 1


section .rodata
    signal:
    .destroy: db "destroy", 0
    .clicked: db "clicked", 0
    title: db "My GTK+3 Window!", 0
    task_text: db "Find root for func: sin(x^2 + 5x)", 0
    btn_result_text: db "Calc", 0
    result: db "Result: ", 0
    entry_1_placeholder: db "x_start", 0
    entry_2_placeholder: db "x_end", 0
    entry_3_placeholder: db "step count", 0

section .data
    ans: db 1000 dup(0)

    start: dq 1
    end: dq 1
    step_count: dq 1

section .text

    _destroy_window:
        jmp gtk_main_quit


    _clicked_calc_btn:
        push rbp

        mov rdi, qword [ rel entry_1 ]
        call gtk_entry_get_text
        mov qword [ rel start ], rax

        mov rdi, qword [ rel entry_2 ]
        call gtk_entry_get_text
        mov qword [ rel end ], rax

        mov rdi, qword [ rel entry_3 ]
        call gtk_entry_get_text
        mov qword [ rel step_count ], rax

        mov rdi, qword [ rel start ]
        mov rsi, qword [ rel end ]
        mov rdx, qword [ rel step_count ]
        call str_func_root

        mov rdi, qword [ rel result_label ]
        mov rsi, ans
        call gtk_label_set_text

        pop rbp

        ret
    
    main:
        push rbp
        mov rbp, rsp
        xor rdi, rdi
        xor rsi, rsi
        call gtk_init

        xor rdi, rdi
        call gtk_window_new

        mov qword [ rel window ], rax
        mov rdi, qword [ rel window ]
        mov rsi, title
        call gtk_window_set_title

        mov rdi, qword [ rel window ]
        mov rsi, GTK_WIN_WIDTH
        mov rdx, GTK_WIN_HEIGHT
        call gtk_window_set_default_size

        mov rdi, qword [ rel window ]
        mov rsi, GTK_WIN_POS_CENTER
        call gtk_window_set_position

        mov rdi, qword [ rel window ]
        mov rsi, signal.destroy
        mov rdx, _destroy_window
        xor rcx, rcx
        xor r8d, r8d
        xor r9d, r9d
        call g_signal_connect_data

        xor rdi, rdi
        xor rsi, rsi
        call gtk_layout_new
        mov qword [ rel layout ], rax

        mov rsi, qword [ rel layout ]
        mov rdi, qword [ rel window ]
        call gtk_container_add

       
        mov rdi, task_text
        call gtk_label_new

        mov rsi, rax
        mov rdi, qword [ rel layout ]
        mov rdx, 200
        mov rcx, 100
        call gtk_layout_put



        xor rdi, rdi
        call gtk_entry_new
        mov qword [ rel entry_1 ], rax


        mov rdi, qword [ rel entry_1 ]
        mov rsi, entry_1_placeholder
        call gtk_entry_set_placeholder_text


        mov rdi, qword [ rel layout ]
        mov rsi, qword [ rel entry_1 ]
        mov rdx, 200
        mov rcx, 200
        call gtk_layout_put


        xor rdi, rdi
        call gtk_entry_new
        mov qword [ rel entry_2 ], rax

        mov rdi, qword [ rel entry_2 ]
        mov rsi, entry_2_placeholder
        call gtk_entry_set_placeholder_text

        
        mov rdi, qword [ rel layout ]
        mov rsi, qword [ rel entry_2 ]
        mov rdx, 200
        mov rcx, 250
        call gtk_layout_put

        xor rdi, rdi
        call gtk_entry_new
        mov qword [ rel entry_3 ], rax

        mov rdi, qword [ rel entry_3 ]
        mov rsi, entry_3_placeholder
        call gtk_entry_set_placeholder_text


        mov rdi, qword [ rel layout ]
        mov rsi, qword [ rel entry_3 ]
        mov rdx, 200
        mov rcx, 300
        call gtk_layout_put

        mov rdi, btn_result_text
        call gtk_button_new_with_label
        mov qword [ rel calc_btn ], rax


        mov rdi, qword [ rel layout ]
        mov rsi, qword [ rel calc_btn ]
        mov rdx, 200
        mov rcx, 350
        call gtk_layout_put


        mov rdi, qword [ rel calc_btn ]
        mov rsi, signal.clicked
        mov rdx, _clicked_calc_btn
        xor rcx, rcx
        xor r8d, r8d
        xor r9d, r9d
        call g_signal_connect_data


        mov rdi, result
        call gtk_label_new
        mov qword [ rel result_label_text ], rax

        mov rdi, qword [ rel layout ]
        mov rsi, qword [ rel result_label_text ]
        mov rdx, 200
        mov rcx, 400
        call gtk_layout_put

        xor rdi, rdi
        call gtk_label_new
        mov qword [ rel result_label ], rax

        mov rdi, qword [ rel layout ]
        mov rsi, qword [ rel result_label ]
        mov rdx, 250
        mov rcx, 400
        call gtk_layout_put

        
        mov rdi, qword [ rel window ]
        call gtk_widget_show_all

        call gtk_main
        
        pop rbp

        ret