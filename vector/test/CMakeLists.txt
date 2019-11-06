project(test_lib_vector)

add_executable(${PROJECT_NAME} test.c)

target_link_libraries(${PROJECT_NAME}
  lib_vector
  )
