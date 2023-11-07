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

cwd=$(pwd)
cd ../build/

if [[ $NO_CLEAN != 1 ]]; then
    echo -e "Cleaning ..."
    rm -rf *
fi

echo -e "Generating Makefile ..."
cmake ../ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../ -DBUILD_SHARED_LIBS=ON

echo -e "Building ..."
make

echo -e "Installing ..."
make install

echo -e "Running ..."
cd ../bin/
./$PROJECT

echo -e "Done."
cd $cwd
