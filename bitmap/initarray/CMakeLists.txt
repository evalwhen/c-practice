project(initarray)
add_library(${PROJECT_NAME} src/initarray.c)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )
