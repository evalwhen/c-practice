project(lib_treemap)

add_library(${PROJECT_NAME} src/treemap.c)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )
