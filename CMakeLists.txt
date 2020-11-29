cmake_minimum_required(VERSION 3.17)
project(xCalc C)

set(CMAKE_C_STANDARD 99)

set(
    XCALC_HEADERS
    src/module.h
    src/app/token.h
    src/app/expression.h
)

set(
    XCALC_SOURCES
    src/app/token.c
    src/app/expression.c
)

include_directories(src)

add_executable(xCalc src/main.c ${XCALC_HEADERS} ${XCALC_SOURCES})
