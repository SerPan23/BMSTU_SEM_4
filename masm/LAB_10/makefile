app.exe : main.asm find_func_root.o
	nasm -f elf64 -o main.o main.asm
	# gcc -m64 main.o find_func_root.o -L/usr/lib/x86_64-linux-gnu $(pkg-config --libs gtk+-3.0) -o app.exe -no-pie
	gcc find_func_root.o main.o -L/usr/lib/x86_64-linux-gnu $(pkg-config --libs gtk+-3.0) -o app.exe -no-pie -lm

test.exe : test.asm
	nasm -f elf64 -o test.o test.asm
	gcc test.o -L/usr/lib/x86_64-linux-gnu $(pkg-config --libs gtk+-3.0) -o test.exe -no-pie

find_func_root.o : find_func_root.c find_func_root.h
	# gcc -std=c99 -no-pie -m80387 -mno-80387 -O0 -c -m64 find_func_root.c
	gcc -std=c99 -c -masm=intel -fPIE find_func_root.c -o find_func_root.o


.PHONY:
run : app.exe
	./app.exe

test : test.exe
	./test.exe

.PHONY:
clean : 
	rm -f *.exe *.o