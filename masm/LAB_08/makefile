run: main.exe
	./main.exe

main.exe: main.o
	g++ main.o -o main.exe

main.o: main.cpp
	g++ -std=c++20 -masm=intel -m80387 -mno-80387 -O0 -c main.cpp

disasm: main.o
	objdump -M intel-mnemonic -d main.o  > dis_main.txt

.PHONY : clean
clean :
	rm -rf *.o *.exe *.out dis_main.txt