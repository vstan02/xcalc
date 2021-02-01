cmake_minimum_required(VERSION 3.17)
project(xCalc C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS)

set(
    XCALC_SOURCES
    src/core/status.c
    src/core/file.c
    src/app/app.c
    src/app/text.c
    src/app/token.c
    src/app/lexer.c
    src/app/parser.c
    src/cli/cli.c
)

set(
    XCALC_TESTS
    src/app/app_tests.c
    src/app/token_test.c
    src/app/text_test.c
    src/app/lexer_test.c
    src/app/parser_test.c
)

include_directories(src)

add_executable(x_calc src/main.c ${XCALC_SOURCES})
add_executable(test src/test.c ${XCALC_TESTS} ${XCALC_SOURCES})

# GTK3
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

target_link_libraries(x_calc ${GTK3_LIBRARIES})
target_link_libraries(test ${GTK3_LIBRARIES})
