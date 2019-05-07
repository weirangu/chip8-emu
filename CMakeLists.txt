cmake_minimum_required (VERSION 3.12)

set(PROJECT_NAME chip8-emu)
set(CMAKE_C_STANDARD 11)

# source files
list(APPEND SOURCES
    src/main.c
    src/render.c
    src/chip8/sys.c
    src/chip8/reg.c
    src/chip8/timers.c
    src/chip8/opcodes.c
)

project(${PROJECT_NAME} C)
add_executable(${PROJECT_NAME} ${SOURCES})

find_package(Curses REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)

# include folder
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include" "${SDL2_INCLUDE_DIRS}")
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES} ${SDL2_LIBRARIES})
