CFLAG=-Wno-implicit-function-declaration

all: main data_proc data_plot
	@echo Compiling...
	gcc $(CFLAG) -o main main.o data_proc.o data_plot.o
	@echo Compiling Done.

clean_win:
	del *.o
	del *.h.gch

clean_linux:
	rm *.o

# Dependencies ===================================
main: main.c
	gcc $(CFLAG) -c main.c

data_proc: data_proc.c data_proc.h
	gcc $(CFLAG) -c data_proc.c

data_plot: data_plot.c data_plot.h
	gcc $(CFLAG) -c data_plot.c
