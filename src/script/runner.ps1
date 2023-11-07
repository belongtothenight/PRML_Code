param(
    [Parameter(Mandatory=$true)][string]$p,
    [Parameter(Mandatory=$false)][switch]$h,
    [Parameter(Mandatory=$false)][switch]$nc
)

Function help () {
    Write-Host "Usage: runner.ps1 -p <project> [-h] [-nc]"
    Write-Host "  -p <program> : project to run"
    Write-Host "  -h           : help"
    Write-Host "  -nc          : no cleaning"
}

if ($h) {
    help
    exit
}

$cwd = Get-Location
cd ../build/

if ($nc) {
    Write-Host "Skipped cleaning."
} else {
    Write-Host "Cleaning ..."
    rm -R *
}

Write-Host "Generating Makefile ..."
cmake ../ CC="C:/MinGW/bin/gcc.exe" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../ -DBUILD_SHARED_LIBS=ON

Write-Host "Building ..."
make

Write-Host "Installing ..."
make install

Write-Host "Running ..."
cd ../bin/
$hw3 = "hw3.exe"
Switch ($p){
    "hw3-all" {
        Invoke-Expression "./${hw3} ../hw3/dataset/shape1.csv ../hw3/dataset/shape2.csv ../hw3/dataset/shape3.csv ../hw3/dataset/shape4.csv ../hw3/dataset/shape5.csv ../hw3/dataset/shape6.csv"
    }
    "hw3-1" {
        Invoke-Expression "./${hw3} ../hw3/dataset/shape1.csv"
    }
    "hw3-2" {
        Invoke-Expression "./${hw3} ../hw3/dataset/shape2.csv"
    }
    "hw3-3" {
        Invoke-Expression "./${hw3} ../hw3/dataset/shape3.csv"
    }
    "hw3-4" {
        Invoke-Expression "./${hw3} ../hw3/dataset/shape4.csv"
    }
    "hw3-5" {
        Invoke-Expression "./${hw3} ../hw3/dataset/shape5.csv"
    }
    "hw3-6" {
        Invoke-Expression "./${hw3} ../hw3/dataset/shape6.csv"
    }
    "hw3" {
        Invoke-Expression "./${hw3}"
    }
    "default" {
        Invoke-Expression "./${hw3}"
    }
}

Write-Host "Done."
cd $cwd
