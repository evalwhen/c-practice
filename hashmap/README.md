## HashMap
    - [X] implement with array using linear probing
        - hash(k, m) - m is size of hash table
        - add(key, value) - if key already exists, update value
        - exists(key)
        - get(key)
        - remove(key)

## Run Test

``` shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ../
make
./test/test_hashmap
```
