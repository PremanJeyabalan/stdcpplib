#ifndef LIB_STRING 
#define LIB_STRING

#include <cstdlib>
#include <iostream>

namespace CustomStd {
    class string {
    public:
        constexpr string() noexcept {
            _short.size_flag = 0;
            _short.buffer[0] = '\0';
        }


        string(const string& str) {
            const size_t size = str.size();
            if (size <= _short_capacity) {
                _short.size_flag = 0;
                set_short_size(size);
            } else {
                _long.capacity = size;
                if ((_long.capacity & 0x01) == 0) _long.capacity++;

                _long.size = size;
                _long.data = new char[_long.capacity + 1];
            }

            memcpy(ptr(), str.data(), capacity() + 1);
        }

//        len = 9
//        0 - 8, cpy from 2 , max = 2 to 8 = 7 chars

        string(const string& str, size_t pos, size_t len = npos) {
            size_t max_len = str.size() - 1 - pos;
            if (len == npos || len > max_len) {
                if (max_len <= _short_capacity) {
                    _short.size_flag = 0;
                    set_short_size(max_len);
                } else {
                    _long.capacity = max_len;
                    if ((_long.capacity & 0x01) == 0) _long.capacity++;

                    _long.size = max_len;
                    _long.data = new char[_long.capacity + 1];
                }

                memcpy(ptr(), str.data(), capacity() + 1);
            } else {
                size_t size = 1 + len;
                if (size <= _short_capacity) {
                    _short.size_flag = 0;
                    set_short_size(size);
                } else {
                    _long.capacity = size;
                    if ((_long.capacity & 0x01) == 0) _long.capacity++;

                    _long.size = size;
                    _long.data = new char[_long.capacity + 1];
                }

                memcpy(ptr(), str.data(), capacity() + 1);
            }
        }

        string(const char* arg) {
            size_t size = strlen(arg);
            if (size <= _short_capacity) {
                _short.size_flag = 0;
                set_short_size(size);
            } else {
                _long.capacity = size;
                if ((_long.capacity & 0x01) == 0) _long.capacity++;

                _long.size = size;
                _long.data = new char[_long.capacity + 1];
            }

            memcpy(ptr(), arg, size+1);
        }

        string(const char* arg, size_t n) {
            size_t size = strlen(arg);

            if (n > size || n < 1) throw std::out_of_range("too large");

            if (n <= _short_capacity) {
                _short.size_flag = 0;
                set_short_size(n);
            } else {
                _long.capacity = n;
                if ((_long.capacity & 0x01) == 0) _long.capacity++;

                _long.size = n;
                _long.data = new char[_long.capacity + 1];
            }

            memcpy(ptr(), arg, n+1);
        }

        string(size_t n, char c) {
            size_t size = n;

            if (size <= _short_capacity) {
                _short.size_flag = 0;
                set_short_size(size);
            } else {
                _long.capacity = size;
                if ((_long.capacity & 0x01) == 0) _long.capacity++;

                _long.size = size;
                _long.data = new char[_long.capacity + 1];
            }

            memset(ptr(), c, n);
        }

        

        ~string() {
            if (!is_short()) delete[] _long.data;
        }

        size_t capacity() {
            return is_short() ?
                _short_capacity : _long.capacity;
        }

        size_t size() const {
            return is_short() ?
                short_size() : _long.size;
        }

        const char* data() const {
            return ptr();
        }

    private:
        constexpr bool is_short() const {
            return !(_short.size_flag & 0x01);
        }

         size_t short_size() const {
            return _short.size_flag >> 1;
        }

        void set_short_size(size_t n) {
            _short.size_flag = n << 1;
        }

        char* ptr() {
            return is_short() ?
                _short.buffer : _long.data;
        }

        const char* ptr() const {
            return is_short() ?
                _short.buffer : _long.data;
        }


    private:
        struct long_t {
            size_t capacity, size;
            char* data;
        };

        static constexpr size_t _short_capacity = sizeof(long_t) - 2;
        static constexpr size_t npos = -1;

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