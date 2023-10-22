CFLAG=-Wno-implicit-function-declaration

data_proc: data_proc.c data_proc.h
	gcc $(CFLAG) -c data_proc.c

main: main.c
	gcc $(CFLAG) -c main.c

all: main data_proc
	@echo Compiling...
	gcc $(CFLAG) -o main main.o data_proc.o
	@echo Compiling Done.

clean_o_win:
	del *.o

clean_o_linux:
	rm *.o
