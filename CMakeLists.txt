cmake_minimum_required(VERSION 3.6)
project(normalmap)

set(CMAKE_C_STANDARD  11)
set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(SOURCE_FILES
        include/stb_image.h
        src/main.c
        src/stb_image.c
        src/normalmap.c
        include/normalmap.h include/stb_image_write.h src/stb_image_write.c)

add_executable(normalmap ${SOURCE_FILES})