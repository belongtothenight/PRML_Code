CFLAG=-Wno-implicit-function-declaration
LIB=./lib/
OUT=./output

all: main data_proc data_plot output_format normal_distribution output_csv decision_boundary
	@echo Compiling...
	gcc $(CFLAG) -o main main.o data_proc.o data_plot.o output_format.o normal_distribution.o output_csv.o decision_boundary.o
	@echo Compiling Done.

clean_win:
	del *.o
	del *.h.gch

clean_linux:
	rm *.o
	rm *.h.gch

# Dependencies ===================================
main: main.c
	gcc $(CFLAG) -c main.c

data_proc: $(LIB)data_proc.c $(LIB)data_proc.h
	gcc $(CFLAG) -c $(LIB)data_proc.c

data_plot: $(LIB)data_plot.c $(LIB)data_plot.h
	gcc $(CFLAG) -c $(LIB)data_plot.c

output_format: $(LIB)output_format.c $(LIB)output_format.h
	gcc $(CFLAG) -c $(LIB)output_format.c

normal_distribution: $(LIB)normal_distribution.c $(LIB)normal_distribution.h
	gcc $(CFLAG) -c $(LIB)normal_distribution.c

output_csv: $(LIB)output_csv.c $(LIB)output_csv.h
	gcc $(CFLAG) -c $(LIB)output_csv.c

decision_boundary: $(LIB)decision_boundary.c $(LIB)decision_boundary.h
	gcc $(CFLAG) -c $(LIB)decision_boundary.c
