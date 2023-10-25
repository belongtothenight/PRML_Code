CFLAG=-Wno-implicit-function-declaration

all: main data_proc data_plot output_format normal_distribution output_csv
	@echo Compiling...
	gcc $(CFLAG) -o main main.o data_proc.o data_plot.o output_format.o normal_distribution.o output_csv.o
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

normal_distribution: normal_distribution.c normal_distribution.h
	gcc $(CFLAG) -c normal_distribution.c

output_csv: output_csv.c output_csv.h
	gcc $(CFLAG) -c output_csv.c
