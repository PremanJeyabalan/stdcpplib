
#ifndef LIB_UNIQUE_PTR
#define LIB_UNIQUE_PTR

#include <cstdlib>
#include<iostream>
#include <tuple>
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
            static_assert(!std::is_pointer_v<deleter_type>, "ensuring no null function pointer deleters");
        }

        unique_ptr(
            pointer_type ptr,
            typename CustomStd::conditional<CustomStd::is_reference_v<deleter_type>, deleter_type, const deleter_type&>::type deleter
        ) : _data(ptr, deleter) {}

        unique_ptr(
            pointer_type ptr,
            CustomStd::remove_reference_t<deleter_type>&& deleter
        ) : _data(std::move(ptr), std::move(deleter)) {
            static_assert(!CustomStd::is_reference_v<deleter_type>, "rvalue deleter cannot be bound to a reference");
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

        unique_ptr& operator=(std::nullptr_t) {
            reset();
            return *this;
        }
        // 
        // OBSERVERS
        pointer_type operator->() const {
            return get();
        }
        
        pointer_type get() const {
            return std::get<0>(_data);
        }

        std::add_lvalue_reference_t<deleter_type> get_deleter() {
            return std::get<1>(_data);
        }

        std::add_lvalue_reference_t<std::add_const_t<deleter_type>> get_deleter() const {
            return std::get<1>(_data);
        }

        //Not sure about this one
        operator bool () const {
            return get() == nullptr;
        }

        //MODIFIERS
        pointer_type release() {
            pointer_type ptr = get();
            std::get<0>(_data) = nullptr;
            return ptr;
        }

        void reset(pointer_type ptr = pointer_type()) {
            if (ptr != get()) {
                get_deleter()(get());
                std::get<0>(_data) = ptr;
            }
        }

        void swap(unique_ptr&& ptr) {
            using std::swap;
            swap(_data, ptr._data);
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

    namespace detail {
        template <typename>
        constexpr bool is_unbounded_array_v = false;

        template <typename T>
        constexpr bool is_unbounded_array_v<T[]> = true;

        template <typename>
        constexpr bool is_bounded_array_v = false;

        template <typename T, std::size_t N>
        constexpr bool is_bounded_array_v<T[N]> = true;
    }

    template <typename T, typename... Ts>
    std::enable_if_t<!std::is_array_v<T>, CustomStd::unique_ptr<T>> make_unique(Ts&&... params) {
        return CustomStd::unique_ptr(new T(std::forward<Ts>(params)...));
    };

    template <typename T>
    std::enable_if_t<detail::is_unbounded_array_v<T>, CustomStd::unique_ptr<T>> make_unique(std::size_t n) {
        return CustomStd::unique_ptr<T>(new std::remove_extent_t<T>[n]());
    }

}

#endif