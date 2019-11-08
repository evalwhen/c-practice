project(lib_linked_list)

# 使用了头指针
add_library(${PROJECT_NAME} src/list.c)
# 不使用额外的头节点以及 size 字段, 使用二级指针简化操作。
add_library(singly_linked_list src/slist.c)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )

target_include_directories(singly_linked_list
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )
