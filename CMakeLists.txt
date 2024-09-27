cmake_minimum_required(VERSION 3.16)

project(oopLab1)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/local/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Werror")

add_library(prog1 srccpp/prog.cpp srccpp/prog.hpp srccpp/dialog.cpp srccpp/dialog.hpp)

link_libraries(prog1)

add_compile_options(--coverage)

add_link_options(--coverage)

add_executable(main srccpp/main.cpp)

add_executable(tests srccpp/tests.cpp srccpp/prog.cpp srccpp/prog.hpp)