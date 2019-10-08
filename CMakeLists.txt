cmake_minimum_required(VERSION 2.8)

project(espSimulator)

set(CMAKE_BINARY_DIR build)

include(config.cmake)

include_directories(${CMAKE_SOURCE_DIR}/src/sdkOverride/include)
include_directories(/usr/include/c++/8)
include_directories(/usr/include/)
include_directories(${PLATFORMIO_PATH}/packages/framework-arduinoespressif8266/cores/esp8266)
include_directories(${PLATFORMIO_PATH}/packages/framework-arduinoespressif8266/tools/sdk/include)
#include_directories(${PLATFORMIO_PATH}/packages/toolchain-xtensa/xtensa-lx106-elf/include)
#include_directories(${PLATFORMIO_PATH}/packages/toolchain-xtensa/xtensa-lx106-elf/include/c++/4.8.2)
#include_directories(${PLATFORMIO_PATH}/packages/toolchain-xtensa/xtensa-lx106-elf/include/c++/4.8.2/xtensa-lx106-elf)
#include_directories(${PLATFORMIO_PATH}/packages/framework-arduinoespressif8266/variants/nodemcu)

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

list(JOIN SOURCES "\n" SOURCES_MSG)
message("Discovered source files:\n${SOURCES_MSG}\n")

file(GLOB_RECURSE sdkOverrideSources ${CMAKE_SOURCE_DIR}/src/sdkOverride/src/*.cpp)
list(APPEND SOURCES ${sdkOverrideSources})

add_executable(espSimulator ${SOURCES})

set_property(TARGET espSimulator PROPERTY CXX_STANDARD 11)
target_compile_options(espSimulator PUBLIC 
    -Wall                   # report all warnings
    -Werror=return-type     # treat no return in function warning as error
    -Wno-parentheses        # don't report unnecessary parantheses warning
    -std=c++11              # use C++11 standard
    -DDEBUG                 # define the DEBUG macro for all sources/headers
    -DDEBUGGER              # enable DBG logging
    -DARDUINO_ARCH_ESP8266  # needed for debug logging
    -march=i686             # compile as i686 32bit architecture
    -pthread                # enable pthread support
    -g                      # generate debug symbols
    -O0                     # disable all optimisations
)
set(CMAKE_CXX_FLAGS "-m32") # tell C++ compiler to generate 32bit code
