cmake_minimum_required(VERSION 3.17)
project(xcalc C)

set(CMAKE_C_STANDARD 11)
set(XCALC_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB XCALC_TESTS "${XCALC_SOURCE_DIR}/**/*_test*.c")
file(GLOB XCALC_SOURCES "${XCALC_SOURCE_DIR}/**/*.c")
list(REMOVE_ITEM XCALC_SOURCES ${XCALC_TESTS})

include_directories(${XCALC_SOURCE_DIR})

find_package(PkgConfig)
pkg_check_modules(GLIB REQUIRED glib-2.0)
include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})
add_definitions(${GLIB_CFLAGS_OTHER})

add_executable(xcalc ${XCALC_SOURCE_DIR}/main.c ${XCALC_SOURCES})
target_link_libraries(xcalc conix)

add_executable(test ${XCALC_SOURCE_DIR}/test.c ${XCALC_TESTS} ${XCALC_SOURCES})
target_link_libraries(test conix ${GLIB_LIBRARIES})

install(TARGETS xcalc RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
