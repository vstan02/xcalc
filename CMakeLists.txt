cmake_minimum_required(VERSION 3.17)
project(
  xcalc
  VERSION 0.2.1
  DESCRIPTION "A fast and simple to use calculator"
  LANGUAGES C
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_C_STANDARD 11 CACHE STRING "The C standard to use")
  set(CMAKE_C_STANDARD_REQUIRED ON)
  set(CMAKE_C_EXTENSIONS ON)

  file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
  if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
  endif()

  include(CheckIPOSupported)
  check_ipo_supported(RESULT IPO_SUPPORTED)
  if(IPO_SUPPORTED)
    message(STATUS "Interprocedural optimization supported")
  else()
    message(STATUS "Interprocedural optimization not supported")
  endif()

  if(MSVC)
    add_compile_options(/W4 /WX)
  else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
  endif()
endif()

set(XCALC_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB XCALC_SOURCES "${XCALC_SOURCE_DIR}/*.c")

add_executable(xcalc ${XCALC_SOURCES})
include_directories(xcalc PRIVATE "${XCALC_SOURCE_DIR}")
target_link_libraries(xcalc conix arithmo)
if(IPO_SUPPORTED)
  set_target_properties(xcalc PROPERTIES INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

install(TARGETS xcalc RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
