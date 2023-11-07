# HW3

Build command: (Execute in base directory)

```bash
cd ./src/build/
cmake ../ -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../ -DBUILD_SHARED_LIBS=ON
make
make install
cd ../bin/
Invoke-Expression ./hw3.exe
cd ../../

```
