project(lib_linked_list)

# 使用了头指针, 以及额外的 size 字段，占用了额外的存储空间。
add_library(${PROJECT_NAME} src/list.c)

# 不使用额外的头节点以及 size 字段, 使用二级指针简化对链表的修改操作。
add_library(singly_linked_list src/slist.c)

target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )

target_include_directories(singly_linked_list
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  )
