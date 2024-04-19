run: main.exe
	./main.exe

main.exe: main.o my_strncpy.o
	gcc main.o my_strncpy.o -o main.exe

my_strncpy.o: my_strncpy.asm
	nasm -f elf64 -o my_strncpy.o my_strncpy.asm

main.o: main.c
	gcc -c main.c

.PHONY : clean
clean :
	rm -rf *.o *.exe *.out