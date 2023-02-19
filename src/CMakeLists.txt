cmake_minimum_required(VERSION 3.25.2)

project(go-plus-plus)

find_package(Curses REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARY})
