cmake_minimum_required (VERSION 2.6)
project (sort_disk_file C)

if (CMAKE_C_COMPILER_ID MATCHES "GUN|Clang")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
endif()

# add_library(memory memory.c)
add_executable(gen_int gen_int.c)
