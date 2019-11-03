project(rotatestr)

add_library(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/src/rotatestr.c)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )
