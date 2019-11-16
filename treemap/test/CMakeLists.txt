project(test_treemap)

add_executable(${PROJECT_NAME} test_treemap.c)

target_link_libraries(${PROJECT_NAME}
  lib_treemap
  )
