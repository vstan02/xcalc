cmake_minimum_required(VERSION 3.17)
project(xcalc C)

set(CMAKE_C_STANDARD 11)

set(
    XCALC_SOURCES
    src/core/status.c
    src/app/calc.c
    src/app/lexer.c
    src/app/parser.c
    src/cli/cli.c
)

set(
    XCALC_TESTS
    src/tests/app_tests.c
    src/app/lexer_test.c
    src/app/parser_test.c
)

include_directories(src)

add_executable(xcalc src/main.c ${XCALC_SOURCES})
add_executable(test src/test.c ${XCALC_TESTS} ${XCALC_SOURCES})

# Conix
target_link_libraries(xcalc conix)
target_link_libraries(test conix)

# GLib
find_package(PkgConfig)
pkg_check_modules(GLIB REQUIRED glib-2.0)

include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})

add_definitions(${GLIB_CFLAGS_OTHER})

target_link_libraries(test ${GLIB_LIBRARIES})
