cmake_minimum_required(VERSION 3.0)

project(shell)

set(CFLAGS  "-g -Werror -Wall")
set(CMAKE_C_FLAGS "${CFLAGS}")

file(GLOB SOURCE_FILES src/*.c)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
