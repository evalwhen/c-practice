cmake_minimum_required (VERSION 3.5)

project(algosort)

add_library(${PROJECT_NAME}
  ${PROJECT_SOURCE_DIR}/src/merge_sort.c
  ${PROJECT_SOURCE_DIR}/src/quick_sort.c
  )

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )

add_executable(algosort_test test.c)

target_link_libraries(algosort_test
  algosort
  )
