project(multibit)

add_library(${PROJECT_NAME}
  src/fourbitmap.c
  )

add_library(multibitmap ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )
