cmake_minimum_required (VERSION 2.6)
project (sort_disk_file C)

if (CMAKE_C_COMPILER_ID MATCHES "GUN|Clang")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
endif()

add_library(bitmap ../bitmap/bitmap.c)
add_library(memory ../bitmap/memory.c)
add_executable(gen_int gen_int.c)
add_executable(sortfile main.c)
add_executable(test_memory test_memory.c)
add_executable(n_pass_sort n_pass_sort.c)
target_link_libraries(sortfile bitmap memory)
target_link_libraries(test_memory memory)

target_link_libraries(n_pass_sort bitmap memory)
