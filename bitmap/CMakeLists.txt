cmake_minimum_required (VERSION 2.6)
project (bitmap_test C)

if (CMAKE_C_COMPILER_ID MATCHES "GUN|Clang")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
endif()

add_library(bitmap bitmap.c)
add_library(fourbitmap fourbitmap.c)
add_library(memory memory.c)
add_executable(bitmap_test test.c)
target_link_libraries(bitmap_test bitmap  fourbitmap memory)
