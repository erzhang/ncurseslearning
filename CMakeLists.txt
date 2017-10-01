cmake_minimum_required( VERSION 3.5 )
project( ncurses_tetris)
set(CMAKE_CXX_STANDARD 11)

file(GLOB SRCS *.cc *.hpp)

add_executable(test_tetris ${SRCS})
target_link_libraries(test_tetris ncurses)

