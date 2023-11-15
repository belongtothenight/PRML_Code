help () {
    echo "Usage: runner.sh -p \"project_name\""
    echo "Usage: runner.sh -p=\"project_name\""
    echo "Usage: runner.sh -h (display this)"
}

while getopts ":h:p:nc": option; do
    case "${option}" in
        p)  PROJECT=${OPTARG};;
        nc) NO_CLEAN=1;;
        h)  help
            exit 1;;
        \?) help
            exit 1;;
    esac
done

if [ -z "$PROJECT" ]
then
    help
    exit 1
fi

FORMAT_BOLD_BLUE="\n\033[1m\033[34m"
FORMAT_RESET="\033[0m"

cwd=$(pwd)
cd ../build/

if [[ $NO_CLEAN != 1 ]]; then
    echo -e "${FORMAT_BOLD_BLUE}Cleaning ...${FORMAT_RESET}"
    rm -rf *
fi

echo -e "${FORMAT_BOLD_BLUE}Generating Makefile ...${FORMAT_RESET}"
cmake ../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../ -DBUILD_SHARED_LIBS=ON

echo -e "${FORMAT_BOLD_BLUE}Building ...${FORMAT_RESET}"
make

echo -e "${FORMAT_BOLD_BLUE}Installing ...${FORMAT_RESET}"
make install

echo -e "${FORMAT_BOLD_BLUE}Running ...${FORMAT_RESET}"
cd ../bin/
./$PROJECT

echo -e "${FORMAT_BOLD_BLUE}Done.${FORMAT_RESET}"
cd $cwd
