param(
    [Parameter(Mandatory=$true)][string]$p,
    [Parameter(Mandatory=$false)][switch]$h,
    [Parameter(Mandatory=$false)][switch]$nc,
    [Parameter(Mandatory=$false)][switch]$spsd,
    [Parameter(Mandatory=$false)][switch]$odw
)

Function help () {
    Write-Host "Usage: runner.ps1 -p <project> [-h] [-nc]"
    Write-Host "  -p <program> : project to run"
    Write-Host "  -h           : help"
    Write-Host "  -nc          : no cleaning"
    Write-Host "  -spsd        : start python simple http server for documentation"
    Write-Host "  -odw         : open documentation in web browser (firefox)"
}

if ($h) {
    help
    exit
}

$output_format = @{
    ForegroundColor = "blue"
    # BackgroundColor = "white"
}

$cwd = Get-Location
cd ../build/

if ($nc) {
    Write-Host "Skipped cleaning." @output_format
} else {
    Write-Host "Cleaning ..." @output_format
    rm -R *
}

Write-Host "Generating Makefiles ..." @output_format
cmake ../ CC="C:/MinGW/bin/gcc.exe" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../ -DBUILD_SHARED_LIBS=ON

Write-Host "Building $p ..." @output_format
make

Write-Host "Installing $p ..." @output_format
make install

Write-Host "Generating documentation ..." @output_format
cd $cwd/../../docs/
doxygen ./Doxyfile

Write-Host "Running $p ..." @output_format
cd $cwd/../bin/
$hw3 = "hw3.exe"
$hw4 = "hw4.exe"
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
    "hw4" {
        Invoke-Expression "./${hw4}"
    }
    "default" {
        Write-Host "Option not found. Running all ..." @output_format
        Invoke-Expression "./${hw3}"
        Invoke-Expression "./${hw4}"
    }
}

if ($spsd) {
    Write-Host "Starting python simple http server ..." @output_format
    Start-Process pwsh -ArgumentList "-c" , {
        Write-Host "Server started at localhost:8000 hosting documentation ..."
        Write-Host "Press Enter to exit" @output_format
        cd $pwd/../../docs/html/
        python "-m http.server --directory ."
        # Read-Host -Prompt "Press Enter to exit"
        Read-Host
    }, "-noexit" -WindowStyle Maximized
}

if ($odw) {
    Write-Host "Opening documentation in web browser ..." @output_format
    Start-Process firefox "--new-tab -url localhost:8000"
}

Write-Host "Done." @output_format
cd $cwd
