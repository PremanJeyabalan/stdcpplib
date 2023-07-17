#ifndef LIB_STRING 
#define LIB_STRING

#include <cstdlib>
#include <string.h>

namespace CustomStd {
    class string {
    public:
        //CONSTRUCTORS

        //default constructor
        string() {
            _short.size_flag = 0;
            _short.buffer[0] = '\0';
        }

        //copy constructor
        string(const string& str) {
            const size_t size = str.size();
            if (size <= _short_capacity) copy_short_string(size, str._short.buffer);
            else copy_long_string(size, str._long.data);
        }

        //substring constructor
        string(const string& str, size_t pos, size_t len = npos) {
            size_t max_len = str.size() -  pos;
            size_t str_size = len == npos || len > max_len ?
                max_len : len;

            if (str_size <= _short_capacity) copy_short_string(str_size, str._short.buffer + pos);
            else copy_long_string(str_size, str._long.data + pos);
        }

        //from c-string
        string(const char* str) {
            size_t size = strlen(str);
            if (size <= _short_capacity) copy_short_string(size, str);
            else copy_long_string(size, str);
        }

        //from buffer
        string(const char* str, size_t n) {
            if (n <= _short_capacity) copy_short_string(n, str);
            else copy_long_string(n, str);
        }

        //fill constructor
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

        //initializer list
        explicit string(std::initializer_list<char> il) {
            if (il.size() <= _short_capacity) copy_short_string(il.size(), std::begin(il));
            else copy_long_string(il.size(), std::begin(il));
        }

        //move constructor
        string(string&& str) noexcept {
            if (str.is_short()) {
                copy_short_string(str.short_size(), str._short.buffer);
                str.set_short_size(0); // consider move efficiency if need to delete here.
                str._short.buffer[0] = '\0';
            } else {
                _long.capacity = str._long.size;
                if ((_long.capacity & 0x01) == 0) _long.capacity++;

                _long.size = str._long.size;
                _long.data = str._long.data;

                str._long.data = nullptr;
                str._short.size_flag = 0;
                str.set_short_size(0);
                str._short.buffer[0] = '\0';
            }
        }

        ~string() {
            if (!is_short()) delete[] _long.data;
        }

        //ASSIGNMENT OPERATORS
        string& operator=(const string& str) {
            if (this == &str) return *this;
            assign(str);
            return *this;
        }

        string& operator=(string&& str) noexcept {
            assign(std::move(str));
            return *this;
        }

        string& operator=(const char* str) {
            assign(str);
            return *this;
        }

        string& operator=(char t) {
            assign(1, t);
            return  *this;
        }

        string& operator=(std::initializer_list<char> ilist) {
            assign(ilist);
            return *this;
        }

        //ASSIGN

        string& assign(size_t count, char c) {
            if (count > capacity()) {
                set_new_long_capacity(count);
                _long.size = count;
                _long.data = new char[_long.capacity + 1];
                memset(_long.data, c, count);
                _long.data[count] = '\0';
            } else {
                char* curr_data = ptr();
                memset(curr_data, c, count);
                curr_data[count] = '\0';
                if (is_short()) set_short_size(count);
                else _long.size = count;
            }

            return *this;
        }

        string& assign(const string& str) {
            const size_t str_size = str.size();

            if (str_size > capacity()) alloc_new_long_string(str_size, str.data());
            else replace_curr_string(str.size(), str.data());

            return *this;
        }

        string& assign(const string& str, size_t pos, size_t count = npos) {
            if (pos > str.size()) throw std::out_of_range("pos invalid");

            const size_t str_size = std::min(str.size() - pos, count);

            if (str_size > capacity()) alloc_new_long_string(str_size, str.data() + pos);
            else replace_curr_string(str_size, str.data() + pos);

            return *this;
        }

        string& assign(string&& str) noexcept {
            if (str.is_short()) copy_short_string(str.short_size(), str._short.buffer);
            else {
                if (!is_short()) delete[] _long.data;

                _long.capacity = str._long.capacity;
                _long.size = str._long.size;
                _long.data = str._long.data;
                str._long.data = nullptr;
                str._long.size = 0;
                str._long.capacity = 0;
            }

            return *this;
        }

        string& assign(const char* str, size_t count) {
           size_t str_size = std::min(strlen(str), count);

           if (str_size > capacity()) alloc_new_long_string(str_size, str);
           else replace_curr_string(str_size, str);

           return *this;
        }

        string& assign(const char* str) {
            size_t str_size = strlen(str);
            return assign(str, str_size);
        }

        string& assign(std::initializer_list<char> ilist) {
            if (ilist.size() > capacity()) alloc_new_long_string(ilist.size(), std::begin(ilist));
            else replace_curr_string(ilist.size(), std::begin(ilist));

            return *this;
        }

        //ELEMENT ACCESS

        char& at(size_t pos) {
            if (pos >= size()) throw std::out_of_range("invalid pos");

            return *(ptr() + pos);
        }

        const char& at(size_t pos) const {
            if (pos >= size()) throw std::out_of_range("invalid pos");

            return *(ptr() + pos);
        }

        char& operator[](size_t pos) {
            return *(ptr() + pos);
        }

        const char& operator[](size_t pos) const {
            return *(ptr() + pos);
        }

        char& front() {
            return operator[](0);
        }

        const char& front() const {
            return operator[](0);
        }

        const char* data() const noexcept {
            return ptr();
        }

        char* data() noexcept {
            return ptr();
        }

        const char* c_str() const noexcept {
            return data();
        }

        char& back() {
            return operator[](size() - 1);
        }

        const char& back() const {
            return operator[](size() - 1);
        }

//      CAPACITY
        bool empty() const noexcept {
            return size() > 0;
        }

        size_t capacity() {
            return is_short() ?
                   _short_capacity : _long.capacity;
        }

        size_t size() const noexcept {
            return is_short() ?
                   short_size() : _long.size;
        }

        size_t length() const noexcept {
            return size();
        }

        void reserve(size_t new_cap = 0) {

        }


    private:
        //short -> LSb = 0
        //long -> LSb = 1
        bool is_short() const {
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

        void copy_short_string(size_t str_size, const char* str) {
            _short.size_flag = 0;
            set_short_size(str_size);

            memcpy(_short.buffer, str, str_size);
        }

        void copy_long_string(size_t str_size, const char* str, size_t capacity = npos) {
            _long.capacity = capacity == npos ? str_size
                    : capacity;
            //must keep odd capacity -> refer to is_short()
            if ((_long.capacity & 0x01) == 0) _long.capacity++;

            _long.size = str_size;
            _long.data = new char[_long.capacity + 1];
            memcpy(_long.data, str, str_size);
            _long.data[_long.size] = '\0';
        }

        void set_new_long_capacity(const size_t str_size) {
            const bool was_short = is_short();
            if (!was_short) delete[] _long.data;

            size_t prev_capacity = _long.capacity;
            _long.capacity = was_short || str_size > 2 * prev_capacity ? str_size
                    : 2 * prev_capacity;

            if ((_long.capacity & 0x01) == 0) _long.capacity++;
        }

        void alloc_new_long_string(const size_t str_size, const char* src)  {
            set_new_long_capacity(str_size);
            copy_long_string(str_size, src, _long.capacity);
        }

        void replace_curr_string(const size_t str_size, const char* src) {
            char* curr_data = ptr();
            memcpy(curr_data, src, str_size);
            curr_data[str_size] = '\0';
            if (is_short()) set_short_size(str_size);
            else _long.size = str_size;
        }

//        void swap(string& other) noexcept {
//            const bool this_short = is_short();
//            const bool other_short = other.is_short();
//
//            if (other_short) {
//                if (!is_short()) delete[] _long.data;
//                copy_short_string(other.short_size(), other._short.buffer);
//            }
//            else {
//                _long.data = other._long.data;
//                _long.size = other._long.size;
//                _long.capacity = other._long.capacity;
//            }
//
//            if (!is_short()) delete[] _long.data;
//        }


    private:
#ifdef LITTLE_ENDIAN
        struct long_t {
            size_t capacity, size;
            char* data;
        };
#else
        struct long_t {
            char* data;
            size_t size, capacity;
        };
#endif

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