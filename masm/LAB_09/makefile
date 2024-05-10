CC = g++

OUTPATH := ./out/
$(shell mkdir -p $(OUTPATH))

SRCS := $(wildcard *.c)

CFLAGS = -std=c++20 -c -O0 -masm=intel -msse -g3

OBJS = $(OUTPATH)main.o $(OUTPATH)matrix.o

app.exe : $(OBJS)
	$(CC) $^ -o $@ -lm

$(OUTPATH)%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPATH)%.d : %.cpp
	$(CC) $(CFLAGS) -MM $< > $@

include $(SRCS:.c=.d)

.PHONY:
debug: app.exe

.PHONY:
run : app.exe
	./app.exe

.PHONY:
clean : 
	rm -f *.exe *.d *.o out/*.o out/*.gcda out/*.gcno