# HW2 - Pinky Dimension Distribution

Code is compiled on Windows 11 x64 platform with command: 

1. ```make main ; .\main.exe ; make clean_win```
2. ```python .\data_gen.py ; make test ; .\test.exe ; make clean_win```

## Dependencies

1. gcc.exe (MinGW-W64 x86_64-ucrt-mcf-seh, built by Brecht Sanders) 13.2.0
2. [gnuplot 5.4 patchlevel 8=>http://www.gnuplot.info/](http://www.gnuplot.info/).

## Directory Structure

1. ```./dataset```: contains the dataset data in CSV format.
2. ```./lib```: c libraries coded for this project.
3. ```./output```: stores the result of this project.
4. ```./data_gen.py```: generate normal distributed data for algorithm testing and debugging.
5. ```./main.c```: the entry point of this project. Process two set of data at a time and also process merged data and their decision boundary.
6. ```./test.c```: testing entry point of this project. Process only one set of data.
7. ```./makefile```: how this project is compiled.
8. ```./readme.md```: this file you're reading, contains documentations.

## Things to complete

1. Diameter to perimeter conversion.
