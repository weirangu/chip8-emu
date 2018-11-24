cmake_minimum_required (VERSION 3.12)

set(PROJECT_NAME chip8-emu)
set(CMAKE_C_STANDARD 11)

# source files
list(APPEND SOURCES
    src/main.c
    src/chip8/sys.c
    src/chip8/cpu.c
)

project(${PROJECT_NAME} C)
add_executable(${PROJECT_NAME} ${SOURCES})

# include folder
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
