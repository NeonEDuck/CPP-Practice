# linkarray

I really hope I can tell the c++ compiler what order the files to compile without Makefile, I might learn that in later day, but for now I will just use another header file to split the implementation of the `linkarray` class.

Implementing `iterator` class is really fun, although I straight out just copy & paste the `std::vector<T>::iterator` code in.

### TodoList
- [ ] Move all class implementation from `linkarray.h` into `linkarray.cpp.h`
  - [ ] `LinkArray<T>::LinkNode`
  - [ ] `LinkArray<T>::iterator`
  - [ ] `LinkArray<T>::reverse_iterator`