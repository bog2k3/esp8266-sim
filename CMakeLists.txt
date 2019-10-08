cmake_minimum_required(VERSION 2.8)

project(espSimulator)

set(CMAKE_BINARY_DIR build)

include(config.cmake)

include_directories(${PLATFORMIO_PATH}/packages/framework-arduinoespressif8266/cores/esp8266)
include_directories(${PLATFORMIO_PATH}/packages/framework-arduinoespressif8266/tools/sdk/include)
include_directories(${PLATFORMIO_PATH}/packages/toolchain-xtensa/xtensa-lx106-elf/include)
include_directories(${PLATFORMIO_PATH}/packages/toolchain-xtensa/xtensa-lx106-elf/include/c++/4.8.2)
include_directories(${PLATFORMIO_PATH}/packages/toolchain-xtensa/xtensa-lx106-elf/include/c++/4.8.2/xtensa-lx106-elf)
include_directories(${PLATFORMIO_PATH}/packages/framework-arduinoespressif8266/variants/nodemcu)

#link_directories(${PLATFORMIO_PATH}/packages/toolchain-xtensa/xtensa-lx106-elf/lib)

MACRO(HEADER_DIRECTORIES return_list)
    FILE(GLOB_RECURSE new_list ${USER_SRC_PATH}/.pio/libdeps/nodemcuv/*.h)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

HEADER_DIRECTORIES(LibraryIncludeDirs)
include_directories(${LibraryIncludeDirs})

file(GLOB_RECURSE headers ${USER_SRC_PATH}/src/*.h)
file(GLOB_RECURSE csources ${USER_SRC_PATH}/src/*.c)
file(GLOB_RECURSE cppsources ${USER_SRC_PATH}/src/*.cpp)
set(SOURCES ${CMAKE_SOURCE_DIR}/src/main.cpp ${headers} ${csources} ${cppsources})

add_executable(espSimulator ${SOURCES})

set_property(TARGET espSimulator PROPERTY CXX_STANDARD 11)
target_compile_options(espSimulator PUBLIC -Wall -Werror=return-type -std=c++11 -march=i686 -DDEBUG)
set(CMAKE_CXX_FLAGS "-m32")
