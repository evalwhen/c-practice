project(test_linked_list)

add_executable(${PROJECT_NAME} test.c)

target_link_libraries(${PROJECT_NAME}
  lib_linked_list
  )
