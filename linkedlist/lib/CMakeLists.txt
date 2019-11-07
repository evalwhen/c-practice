project(lib_linked_list)

add_library(${PROJECT_NAME} src/list.c)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )
