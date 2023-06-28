#ifndef LIB_STRING 
#define LIB_STRING

#include <cstdlib>
#include <iostream>

namespace CustomStd {
    class string {
    public:
        string() : _short.size_flag(0) {
            _short.buffer[0] = '\0';
        }


    private:
        struct long_t {
            size_t capacity, size;
            char* data;
        };

        static constexpr size_t _short_capacity = sizeof(long_t) - 2;

        struct short_t {
            unsigned char size_flag;
            char buffer[_short_capacity + 1];
        };

        union {
            long_t _long;
            short_t _short;
        };
    };
}

#endif