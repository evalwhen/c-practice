project(caculator)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/main.c)

target_link_libraries(${PROJECT_NAME}
  stack
  )
