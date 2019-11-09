## [Linked List](https://github.com/evalwhen/coding-interview-university#data-structures)
    - [ ] implement (I did with tail pointer & without):
        - [X] size() - returns number of data elements in list
        - [X] empty() - bool returns true if empty
        - [X] value_at(index) - returns the value of the nth item (starting at 0 for first)
        - [X] push_front(value) - adds an item to the front of the list
        - [X] pop_front() - remove front item and return its value
        - [X] push_back(value) - adds an item at the end
        - [X] pop_back() - removes end item and returns its value
        - [X] front() - get value of front item
        - [X] back() - get value of end item
        - [X] insert(index, value) - insert value at index, so current item at that index is pointed to by new item at index
        - [X] erase(index) - removes node at given index
        - [X] value_n_from_end(n) - returns the value of the node at nth position from the end of the list
        - [X] reverse() - reverses the list
        - [X] remove_value(value) - removes the first item in the list with this value
    - [ ] Doubly-linked List
        - [Description (video)](https://www.coursera.org/learn/data-structures/lecture/jpGKD/doubly-linked-lists)
        - No need to implement

## Run Test

``` shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ../
make
./test/test_slist
```
