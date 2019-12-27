How to build this game:
1. Install SFML from your package manager or this website: https://www.sfml-dev.org/index.php
2. Install CMake from this website: https://cmake.org/download/
3. In "CMakeLists.txt"
    1. Change the "include_directories" command to reflect the location of the folder containing the SFML header files
    2. Change the "target_link_libraries" commands to reflect the location of the SFML library files
4. Run CMake, choosing "cmake_build_debug" for "where to build the binaries" and the root folder of the repo for "where is the source code"
5. Generate a makefile with cmake, then run make to build the final binary

