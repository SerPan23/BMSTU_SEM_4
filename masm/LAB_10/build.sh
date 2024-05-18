#!/bin/bash
rm -f *.exe *.o

gcc -std=c99 -c -masm=intel -fPIE find_func_root.c -o find_func_root.o
nasm -f elf64 -o main.o main.asm
gcc find_func_root.o main.o -L/usr/lib/x86_64-linux-gnu $(pkg-config --libs gtk+-3.0) -o app.exe -no-pie -lm
# ./app.exe