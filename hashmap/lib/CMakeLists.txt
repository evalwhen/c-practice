project(lib_hashmap)

add_library(${PROJECT_NAME} src/hashmap.c)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )
