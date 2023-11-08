# HW3

There are two methods included in here. 

1. ```./gen_shape.gp``` to produce hard coded shapes. Execute with ```gnuplot ./gen_shape.gp```.
2. ```./main.c``` which is coded as CLI tool to take CSV coordinate pair as input. Execute with ```./src/script/runner.ps1 -p hw3-all```.

## Dependencies

1. CMake
2. GCC
3. OpenSSL
4. GNUPlot

## Directory Structure

1. ```./dataset```: coordinate of original shapes.
2. ```./lib```: libraries files for c code.
3. ```./output```: output images and data files (not included) generated from c program and ```gen_shape.gp```.
4. ```./CMakeLists.txt```: CMake sub-directory settings for hw3, need to be built from ```./src/CMakeLists.txt```.
5. ```./gen_shape.gp```: seperate program with c, generate images with user input coordinates.
6. ```./main.c```: entry point of c program in hw3.
7. ```./readme.md```: this file you see.

## Problems

1. It is unnecessary to keep opening and closing GNUPlot pipes.
2. Can't auto detect shapes category even if they looks the same on image. (currently: coordinate concatenated string hashing string)
