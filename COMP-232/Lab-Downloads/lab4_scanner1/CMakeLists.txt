cmake_minimum_required(VERSION 3.8)
project(scanner1)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        src/main.c
        src/scanner.h
        src/scanner_ad_hoc.c)

include_directories(AFTER src)

add_executable(scanner1 ${SOURCE_FILES})