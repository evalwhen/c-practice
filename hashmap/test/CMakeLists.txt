project(test_hashmap)

add_executable(${PROJECT_NAME} test_hashmap.c)

target_link_libraries(${PROJECT_NAME}
  lib_hashmap
  )
