#ifndef LIB_TYPE_TRAITS
#define LIB_TYPE_TRAITS

#include <cstdlib>
#include <iostream>

namespace CustomStd {
    template <typename T> 
    struct is_reference {
        static const bool value = false;
    };

    template <typename T> 
    struct is_reference<T&> {
        static const bool value = true;
    };

    template <typename T> 
    struct is_reference<T&&> {
        static const bool value = true;
    };

    template <typename T>
    inline bool is_reference_v = is_reference<T>::value;

    template <typename T>
    struct remove_reference {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&> {
        using type = T;
    };

    template <typename T>
    struct remove_reference<T&&> {
        using type = T;
    };

    template <typename T>
    using remove_reference_t = typename remove_reference<T>::type;

    template <typename T>
    struct is_floating_point {
        static const bool value = false;
    };
    
    template <>
    struct is_floating_point<float> {
        static const bool value = true;
    };
    template <>
    struct is_floating_point<double> {
        static const bool value = true;
    };
    template <>
    struct is_floating_point<long double> {
        static const bool value = true;
    };
}

#endif