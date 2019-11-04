cmake_minimum_required (VERSION 3.5)

# the c programming language
project(tcpl)

add_subdirectory(getline)

# test binary
add_subdirectory(test)

# caculator app
add_subdirectory(caculator)


add_subdirectory(stack)
