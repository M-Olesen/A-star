cmake_minimum_required(VERSION 3.0.0)
project(AStar VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(AStar main.c
        stack.h
        InputOutput.c
        InputOutput.h
        TSP.c
        TSP.h
)

add_library(search search.c)
target_include_directories(search PUBLIC .)
target_link_libraries(AStar search)

add_library(stack stack.c)
target_include_directories(stack PUBLIC .)
target_link_libraries(AStar stack)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
