cmake_minimum_required(VERSION 3.17)
project(xCalc C)

set(CMAKE_C_STANDARD 99)

set(
    XCALC_HEADERS
    src/core/test.h
    src/core/module.h
    src/core/error.h
    src/app/token.h
    src/app/lexer.h
    src/app/interpreter.h
    src/app/expression.h
)

set(
    XCALC_SOURCES
    src/core/error.c
    src/app/token.c
    src/app/lexer.c
    src/app/interpreter.c
    src/app/expression.c
)

set(
    XCALC_TESTS
    src/app/token_test.c
    src/app/expression_test.c
    src/app/lexer_test.c
    src/app/interpreter_test.c
)

include_directories(src)

add_executable(x_calc src/main.c ${XCALC_HEADERS} ${XCALC_SOURCES})
add_executable(test src/test.c ${XCALC_TESTS} ${XCALC_HEADERS} ${XCALC_SOURCES})

# GTK3
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(test ${GTK3_LIBRARIES})
