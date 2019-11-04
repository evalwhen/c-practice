project(stack)

add_library(${PROJECT_NAME} src/stack.c src/getop.c)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )
