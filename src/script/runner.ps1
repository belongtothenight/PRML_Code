param($p="hw3")

$cwd = Get-Location

Write-Host "Generating Makefile..."
cd ../build/
cmake ../ CC="C:/MinGW/bin/gcc.exe" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../ -DBUILD_SHARED_LIBS=ON

Write-Host "Building..."
make

Write-Host "Installing..."
make install

Write-Host "Running..."
cd ../bin/
Write-Host $p
Invoke-Expression "./$p.exe"
cd $cwd

Write-Host "Done."
