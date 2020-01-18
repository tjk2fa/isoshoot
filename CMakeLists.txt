cmake_minimum_required(VERSION 3.15)
project(game)

set(CMAKE_CXX_STANDARD 14)

add_executable(game main.cpp Game.cpp Game.h gameMap.cpp gameMap.h Entity.cpp Entity.h Entity.cpp Entity.h)

include_directories("/opt/local/include")

target_link_libraries(game "/opt/local/lib/libsfml-graphics.dylib")
target_link_libraries(game "/opt/local/lib/libsfml-window.dylib")
target_link_libraries(game "/opt/local/lib/libsfml-system.dylib")