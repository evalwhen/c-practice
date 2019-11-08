project(test_linked_list)

add_executable(${PROJECT_NAME} test.c)
add_executable(test_slist test_slist.c)

target_link_libraries(${PROJECT_NAME}
  lib_linked_list
  )

target_link_libraries(test_slist
  singly_linked_list
  )
