project(singlebit)
add_library(${PROJECT_NAME} src/bitmap.c)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )
