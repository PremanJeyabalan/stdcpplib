# stdcpplib
Collection of my implementations of STL containers and other functions

## TODO
Make list of stl containers and functions I want to replicate, or new ones to create (ex concurrent_hashmap).


### Current List (Tick means in progress/finished)
- [X] Vector (SBO)
- [X] String (SSO)
- [X] Unique Ptr + Make Unique + Deleter
- [ ] Unordered + Ordered Map
- [ ] Shared Ptr + Make Shared + Deleter
- [ ] Concurrent Hashmap

## vector
Added initial implementation of vector, still needs full allocator functionality, use of uniqu ptrs(self created), initializer list, exception safe, thread safety (maybe...).

## Learning I've gained from implementations

### Unique Pointer
1. 2 Move constructors, 1 for same type, and another for implicit type conversions, like from derived class to base.
2. Pointer to member variable typedefs

## Learning I've gained from implementations

### Unique Pointer
1. 2 Move constructors, 1 for same type, and another for implicit type conversions, like from derived class to base.
2. Pointer to member variable typedefs
3. Use cases for constexpr and noexcept, especially for constructors
4. SFINAE templates for constructors

