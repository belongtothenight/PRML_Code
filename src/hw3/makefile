CFLAG=-Wno-implicit-function-declaration
LIB=./lib/
OUT=./output

main: main_code data_proc data_plot output_format output_csv
	@echo Compiling...
	gcc $(CFLAG) main.c -o main -lm main.o data_proc.o data_plot.o output_format.o output_csv.o
	@echo Compiling Done.

clean_win:
	del *.o
	del *.h.gch

clean_linux:
	rm *.o
	rm *.h.gch

# Dependencies ===================================
data_proc: $(LIB)data_proc.c $(LIB)data_proc.h
	gcc $(CFLAG) -c $(LIB)data_proc.c

data_plot: $(LIB)data_plot.c $(LIB)data_plot.h
	gcc $(CFLAG) -c $(LIB)data_plot.c

output_format: $(LIB)output_format.c $(LIB)output_format.h
	gcc $(CFLAG) -c $(LIB)output_format.c

output_csv: $(LIB)output_csv.c $(LIB)output_csv.h
	gcc $(CFLAG) -c $(LIB)output_csv.c
