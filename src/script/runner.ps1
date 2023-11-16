param(
    [Parameter(Mandatory=$true)][string]$p,
    [Parameter(Mandatory=$false)][switch]$h,
    [Parameter(Mandatory=$false)][switch]$nc,
    [Parameter(Mandatory=$false)][switch]$spsd,
    [Parameter(Mandatory=$false)][switch]$odw,
    [Parameter(Mandatory=$false)][switch]$dgp
)

Function help () {
    Write-Host "Usage: runner.ps1 -p <project> [-h] [-nc]"
    Write-Host "  -p <program> : project to run"
    Write-Host "  -h           : help"
    Write-Host "  -nc          : no cleaning"
    Write-Host "  -spsd        : start python simple http server for documentation"
    Write-Host "  -odw         : open documentation in web browser (firefox)"
    Write-Host "  -dgp         : deploy documentation to github pages"
}

if ($h) {
    help
    exit
}

$output_format = @{
    ForegroundColor = "blue"
    # BackgroundColor = "white"
}

$project_dir = "E:/GitHub/PRML_Code/"
cd $project_dir/src/build/

if ($nc) {
    Write-Host "`nSkipped cleaning." @output_format
} else {
    Write-Host "`nCleaning ..." @output_format
    rm -R *
}

Write-Host "`nGenerating Makefiles ..." @output_format
cmake ../ CC="C:/MinGW/bin/gcc.exe" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../ -DBUILD_SHARED_LIBS=ON

Write-Host "`nBuilding $p ..." @output_format
make

Write-Host "`nInstalling $p ..." @output_format
make install

Write-Host "`nRunning $p ..." @output_format
cd $project_dir/src/bin/
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
        Invoke-Expression "./${hw4} ../hw4/config.ini"
    }
    "default" {
        Write-Host "`nOption not found. Running all ..." @output_format
        Invoke-Expression "./${hw3}"
        Invoke-Expression "./${hw4}"
    }
}

Write-Host "`nGenerating documentation ..." @output_format
cd $project_dir/docs/
doxygen ./Doxyfile

if ($spsd) {
    Write-Host "`nStarting python simple http server ..." @output_format
    Start-Process pwsh -ArgumentList "-c" , {
        Write-Host "Server started at localhost:8000 hosting documentation ..."
        Write-Host "Press Enter to exit"
        python "-m http.server --directory E:/GitHub/belongtothenight.github.io/docs/PRML_Code/"
        # Read-Host -Prompt "Press Enter to exit"
        Read-Host
    }, "-noexit" -WindowStyle Maximized
}

if ($odw) {
    Write-Host "`nOpening documentation in web browser ..." @output_format
    Start-Process firefox "--new-tab -url localhost:8000"
}

if ($dgp) {
    Write-Host "`nDeploying to github pages ..." @output_format
    cd $project_dir/../belongtothenight.github.io/
    git add .
    git commit -m "Deploy to GitHub Pages"
    git push -f
    Start-Process firefox "--new-tab -url https://github.com/belongtothenight/belongtothenight.github.io/actions"
}

Write-Host "`nDone." @output_format
cd $project_dir/src/script/
