CFLAG=-Wno-implicit-function-declaration

all: main data_proc data_plot output_format
	@echo Compiling...
	gcc $(CFLAG) -o main main.o data_proc.o data_plot.o output_format.o
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

output_format: output_format.c output_format.h
	gcc $(CFLAG) -c output_format.c
