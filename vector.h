#ifndef LIB_VECTOR 
#define LIB_VECTOR

#include <cstdlib>
#include<iostream>

namespace epc
{
   template <typename T, size_t N>
   class vector
   {
      public:
         vector() noexcept : _capacity(N), _size(0), _exist(false), _data(ptr()) {}

         vector(const vector& other) : _size(other.size()), _capacity(other.capacity()), _exist(other._exist) {
            _data = (_exist) ? (T*)::operator new(sizeof(T) * _capacity) : ptr();

            size_t i = 0;
            try {
               for (; i < _size; i++) new (_data + i) T(other[i]);
            } catch (...) {
               for (; i > 0; i--) std::destroy_at(_data + i - 1);
               _size = 0;
               if (_exist) ::operator delete(_data);
               throw;
            }
         }

         vector& operator=(const vector& other) {
            if (&other == this) return *this;
            
            auto temp {other};

            swap(temp);

            return *this;
         }

         vector(vector&& other) : _size(other._size), _capacity(other._capacity), _exist(other._exist) {
            //if dynamic memory is being used, just take over ownership of memory, otherwise, move contents of old buffer to new buffer
            if (_exist) {
               _data = other._data;
               other._data = nullptr;
               other._size = 0;
            } else {
               _data = ptr();

               size_t i = 0;
               try {
                  for (; i < _size; i++) new (_data + i) T(std::move(other[i]));
               } catch (...) {
                  for (; i > 0; i--) std::destroy_at(_data + i - 1);
                  _size = 0;
                  throw;
               }
               other.clear();
            }
         }

         vector& operator=(vector&& other) {
            if (&other == this) return *this;

            auto temp {std::move(other)};

            swap(temp);

            return *this;
         }


         ~vector() {
            for (size_t i = 0; i < _size; i++) std::destroy_at(_data+i);
            if (_exist) ::operator delete(_data);
         }

         T* data() {return _data; }
         const T* data() const { return _data; }

         T& operator[](size_t index) { return *(_data + index); }
         const T& operator[](size_t index) const { return *(_data + index); }

         size_t capacity() const {  return _capacity; }
         size_t size() const { return _size; }

         void reserve(size_t capacity) {
            if (capacity <= _capacity) return;

            T* data = (T*)::operator new(capacity * sizeof(T));

            size_t i = 0;

            try {
               for (; i < _size; i++) new (data + i) T(std::move_if_noexcept(*(_data + i)));
            } catch (...) {
               for (; i > 0; i--) std::destroy_at(data + i - 1);
               _size = 0;
               ::operator delete(data);
               throw;
            }

            size_t size = _size;
            clear();

            if (_exist) ::operator delete(_data);

            _data = data;
            _capacity = capacity;
            _size = size;
            _exist = true;
         }

         void push_back(const T& value) {
            emplace_back(value);
         }

         void push_back(T&& value) {
            emplace_back(std::move(value));
         }

         template <typename... Ts>
         void emplace_back(Ts&&... value) {
            if (_size == _capacity) reserve(_capacity > 0 ? _capacity * 2 : 1);
            new (_data + _size) T(std::forward<Ts>(value)...);
            _size++;
         }

         void pop_back() { 
            if (_size == 0) return;

            std::destroy_at(_data + --_size);
         } 

         void clear() {
            for (;_size > 0; _size--) std::destroy_at(_data + _size - 1);
         }

         void swap(vector& other) noexcept {
            const bool thisShort = !_exist;
            const bool otherShort = !other._exist;
            const int vectorSizeCases = thisShort + otherShort;

            std::swap(_capacity, other._capacity);
            std::swap(_size, other._size);
            std::swap(_exist, other._exist);

            switch (vectorSizeCases) {
               case 2: {
                  const int smaller = std::min(_size, other._size);
                  const int larger = std::max(_size, other._size);
                  //sizes swapped already
                  //if this size was smaller, placement new into this, call destructor for other. vice versa otherwise.
                  int i = 0;
                  if (other._size == smaller) {

                     for (; i < larger; i++) {
                        //swap inner elements for smaller where data is defined
                        if (i < smaller) {
                           std::swap(*(_buffer + i), *(other._buffer + i));
                           continue;
                        }

                        try {
                           new (_buffer + i) T(std::move_if_noexcept(*(other._buffer + i)));
                        } catch (...) {
                           int j = i;
                           for (; i > 0; i--) std::destroy_at(_buffer + i - 1);
                           for (; j < larger; j++) std::destroy_at(other._buffer + j);
                           _size = 0;
                           throw;
                        }

                        std::destroy_at(other._buffer + i);

                     }
                  } else {
                     
                     for (; i < larger; i++) {
                        //swap inner elements for smaller where data is defined
                        if (i < smaller) {
                           std::swap(*(_buffer + i), *(other._buffer + i));
                           continue;
                        }

                        try {
                           new (other._buffer + i) T(std::move_if_noexcept(*(_buffer + i)));
                        } catch (...) {
                           int j = i;
                           for (; i > 0; i--) std::destroy_at(other._buffer + i - 1);
                           for (; j < larger; j++) std::destroy_at(_buffer + j);
                           other._size = 0;
                           throw;
                        }

                        std::destroy_at(_buffer + i);
                     }
                  }

                  _data = ptr();
                  other._data = other.ptr();
                  return;
               }
               case 1: {
                  //sizes swapped already
                  //this is short, other is long -> this _data steals other _data, other copy/moves this _buffer into other _buffer, destroy at this _buffer.
                  // vice versa otherwise.
                  int i = 0;
                  if (thisShort) {
                     _data = other._data;
                     for (; i < other._size; i++) {
                        try {
                           new (other._buffer + i) T(std::move_if_noexcept(*(_buffer + i)));
                        } catch (...) {
                           int j = i;
                           for (; i > 0; i--) std::destroy_at(other._buffer + i - 1);
                           for (; j < other._size; j++) std::destroy_at(_buffer + j);
                           other._size = 0;
                           throw;
                        }
                        std::destroy_at(_buffer + i);
                     }
                     other._data = other.ptr();
                  } else {
                     other._data = _data;
                     for (; i < _size; i++) {
                        try {
                           new (_buffer + i) T(std::move_if_noexcept(*(other._buffer + i)));
                        } catch (...) {
                           int j = i;
                           for (; i > 0; i--) std::destroy_at(_buffer + i - 1);
                           for(; j < _size; j++) std::destroy_at(other._buffer + j);
                           _size = 0;
                           throw;
                        }
                        std::destroy_at(other._buffer + i);
                     }
                     _data = ptr();
                  }

                  return;
               }
               default:
                  std::swap(_data, other._data);
                  return; 
            } 
            
         }

         friend std::ostream& operator<<(std::ostream& os, const vector& v) {
            os << "----------------" << std::endl;
            os << "[";

            for (size_t i = 0; i < v.size(); i++) os << v[i] << ", ";

            os << "]" << std::endl;
            os << "_size: " << v.size() << std::endl;
            os << "_capacity: " << v.capacity() << std::endl;
            os << "----------------" << std::endl;

            return os;
         }

      private:
         size_t _capacity;
         size_t _size;
         bool _exist;
         std::aligned_storage_t<sizeof(T), alignof(T)> _buffer[N];
         T* _data;

         inline T* ptr() {return reinterpret_cast<T*>(_buffer);}
   };
}

#endif
