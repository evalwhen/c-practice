# cmake_minimum_required (VERSION 2.6)
# project (bitmap_test C)

# if (CMAKE_C_COMPILER_ID MATCHES "GUN|Clang")
#   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic -Wall")
# endif()

# add_library(bitmap bitmap.c)
# add_library(fourbitmap fourbitmap.c)
# add_library(memory memory.c)
# add_executable(bitmap_test test.c)
# target_link_libraries(bitmap_test bitmap  fourbitmap memory)


cmake_minimum_required (VERSION 3.5)

project(bitmap)

# bitmap usecase
add_subdirectory(sortfile)

# lib: bitmap
add_subdirectory(singlebit)

# lib: repeatable bitmap
add_subdirectory(multibit)

# lib: little memory reporter
add_subdirectory(memoryusage)
