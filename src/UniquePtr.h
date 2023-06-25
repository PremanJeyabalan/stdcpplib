
#ifndef LIB_UNIQUE_PTR
#define LIB_UNIQUE_PTR

#include <cstdlib>
#include<iostream>
#include "TypeTraits.h"

namespace CustomStd {
    template <typename T>
    struct default_delete {
        default_delete() {}

        template <typename U>
        default_delete(const default_delete<U>&) {}

        void operator()(T* ptr) const {
            static_assert(sizeof(T) > 0, "Class type needs to be complete, incomplete types cannot be deleted");

            delete ptr;
        }
    };

    template <typename T>
    struct default_delete<T[]> {
        void operator()(T* ptr) const {
            static_assert(sizeof(T) > 0, "Class type needs to be complete, incomplete types cannot be deleted");

            delete[] ptr;
        }
    };
    template <typename T, typename D = CustomStd::default_delete<T>>
    class unique_ptr {
        typedef std::tuple<T*, D> tuple_data_type;

    public:
        typedef T* pointer_type;
        typedef T element_type;
        typedef D deleter_type;

        //CONSTRUCTORS

        unique_ptr() : _data(element_type(), deleter_type()) {
            static_assert(!std::is_pointer<deleter_type>::value, "ensuring no null function pointer deleters");
        }

        explicit unique_ptr(pointer_type ptr) : _data(ptr, deleter_type()) {
            static_assert(!std::is_pointer_v<pointer_type>, "ensuring no null function pointer deleters");
        }

        unique_ptr(
            pointer_type ptr,
            typename CustomStd::conditional<CustomStd::is_reference_v, deleter_type, const deleter_type&>::type deleter
        ) : _data(ptr, deleter) {}

        unique_ptr(
            pointer_type ptr,
            CustomStd::remove_reference_t<deleter_type>&& deleter
        ) : _data(std::move(ptr), std::move(deleter)) {
            static_assert(!CustomStd::is_reference_v<deleter_type>, "rvalue deleter cannot be bound to a reference")
        }

        //MOVE CONSTRUCTORS

        unique_ptr(unique_ptr&& src) : 
            _data(src.release(), std::forward<deleter_type>(src.get_deleter())) {}

        template<typename U, typename U_D>
        unique_ptr(unique_ptr<U, U_D>&& src) :
            _data(src.release(), std::forward<deleter_type>(src.get_deleter())) {}

        //DESTRUCTOR

        ~unique_ptr() {
            reset();
        }
        
        //ASSIGNMENT OPERATORS
        
        unique_ptr& operator=(unique_ptr&& src) {
            reset(src.release());
            get_deleter() = std::move(src.get_deleter());
            return *this;
        }

        template <typename U, typename U_D>
        unique_ptr& operator=(unique_ptr<U, U_D>&& src) {
            reset(src.release());
            get_deleter() = std::move(src.get_deleter());
            return *this;
        }

        // TODO: MOVE ASSIGNMENT OPERATOR WITH TYPEDEF

        // 

        pointer_type operator->() const {
            return get();
        }
        
        pointer_type get() const {
            return std::get<0>(_data);
        }

        

        //DISABLE COPY AND COPY ASSIGNMENT OPERATORS
        unique_ptr(const unique_ptr&) = delete;
        
        template <typename U, typename U_D>
        unique_ptr(const unique_ptr<U, U_D>&) = delete;


        unique_ptr& operator=(const unique_ptr&) = delete;
        
        template <typename U, typename U_D>
        unique_ptr& operator=(const unique_ptr<U, U_D>&) = delete;

    private:
        tuple_data_type _data;
    };

    template <typename T, typename... Ts>
    CustomStd::unique_ptr<T> make_unique(Ts&&... params) {
        return CustomStd::unique_ptr(new T(std::forward<Ts>(params...)));
    };

}

#endif