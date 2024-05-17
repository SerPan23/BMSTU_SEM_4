bits 64
global main
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

section .bss
    window: resq 1

section .rodata
    signal:
    .destroy: db "destroy", 0
    title: db "My GTK+3 Window!", 0

section .text

    _destroy_window:
    jmp gtk_main_quit
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
    mov rdi, qword [ rel window ]
    call gtk_widget_show
    call gtk_main
    ret