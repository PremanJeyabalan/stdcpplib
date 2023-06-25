# stdcpplib
Collection of my implementations of STL containers and other functions

## TODO
Make list of stl containers and functions I want to replicate, or new ones to create (ex concurrent_hashmap).


### Current List (Tick means in progress/finished)
- [X] Vector (SBO)
- [ ] String (SSO)
- [ ] Unique Ptr + Make Unique + Deleter
- [ ] Shared Ptr + Make Shared + Deleter
- [ ] Unordered + Ordered Map
- [ ] Dequeue
- [ ] Array
- [ ] Pair
- [ ] Tuple
- [ ] List
- [ ] Concurrent Hashmap

## vector
Added initial implementation of vector, still needs full allocator functionality, use of uniqu ptrs(self created), initializer list, exception safe, thread safety (maybe...).

## Learning I've gained from implementations

### Unique Pointer
1. 2 Move constructors, 1 for same type, and another for implicit type conversions, like from derived class to base.
2. Pointer to member variable typedefs


