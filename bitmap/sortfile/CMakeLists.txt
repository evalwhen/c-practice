project(sortfile)

add_executable(${PROJECT_NAME} sortfile.c)
add_executable(gen_int gen_random.c)
add_executable(test test.c)
add_executable(n_pass_sort n_pass_sort.c)
add_executable(dup_sortfile dup_sortfile.c)
add_executable(init_array init_array.c)

target_link_libraries(${PROJECT_NAME}
  singlebit
  memoryusage
  )

target_link_libraries(test
  singlebit
  multibit
  memoryusage
  )

target_link_libraries(n_pass_sort
  singlebit
  memoryusage
  )

target_link_libraries(dup_sortfile
  multibit
  memoryusage
  )

target_link_libraries(init_array
  initarray
  memoryusage
  )


