# SRC

Return to [documentation homepage](https://belongtothenight.github.io/PRML_Code_Docs/).

This directory contains all source code and related files of this repository.

Note: This likely isn't the lastest content, visit [PRML_Code repository](https://github.com/belongtothenight/PRML_Code) for up-to-date content.

## Directory Structure

hwX directories contains source code for each homework.

1. ```./bin```: executable files. (not static, updated by other part of src) (start support from hw3)
2. ```./build```: not included here. (cmake build directory) (start support from hw3)
3. ```./libc```: shared c libraries in this repo. (start support from hw3)
4. ```./script```: script to clean, compile, install, and execute each project. (start support from hw3)
5. ```./CMakeLists.txt```: cmake project settings for entire repo. (start support from hw3)
6. ```./readme.md```: this file.

## Dependencies

1. [PowerShell7 - 7.3.9](https://github.com/PowerShell/PowerShell) Deployment pipeline on windows.
2. [CMake - 3.27.2](https://cmake.org/) Managing make.
3. [Make - 4.3](https://www.gnu.org/software/make/) Making C dependencies.
4. [GCC - MinGW-W64 x86_64-ucrt-mcf-seh, built by Brecht Sanders 13.2.0](https://gcc.gnu.org/) Compiling C dependencies on windows.
5. [Doxygen - 1.9.7](https://www.doxygen.nl/) Generating documentation.
6. [doxygen-awesome-css - 2.2.1](https://github.com/jothepro/doxygen-awesome-css) Modify default doxygen generated html.
7. [Graphviz - 9.0.0](https://www.graphviz.org/) Requirement for Doxygen - Dot.
8. [Python - 3.10.8](https://www.python.org/) Launching http server locally for testing.
9. [Firefox - 119.0.1](https://www.mozilla.org/en-US/firefox/new/) Launching webpage to view changes.
10. [Git - 2.42.0.windows.2](https://git-scm.com/) Deploying local changes to github.

## Deploy doxygen-awesome-css Doxyfile settings

Matching ```./docs/Doxyfile``` (used for generating docs) with ```./docs/doxygen-awesome-css/Doxyfile``` (template provided by doxygen-awesome-css, require following installation steps), focusing on settings like HTML_EXTRA_STYLESHEET, HTML_COLORSTYLE, GENERATE_TREEVIEW.
