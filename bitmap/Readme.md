## generate Makefile
cmake -DCMAKE_BUILD_TYPE=Debug .

## build
make

## run test

./bitmap_test

## debug

1. 3357 segmentation fault (core dumped)

  use this method to print call stack.

  valgrind -v ./bitmap_test
  
   
