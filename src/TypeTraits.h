#ifndef LIB_TYPE_TRAITS
#define LIB_TYPE_TRAITS

#include <cstdlib>
#include <iostream>

namespace CustomStd {

    template <class T, T v>
    struct integral_constant {
        static constexpr T value = v;
        using value_type = T;
        using type = integral_constant;
        constexpr operator value_type() const noexcept {
            return value;
        }
        const value_type operator()() const noexcept {
            return value;
        }
    };

    template <bool B>
    using bool_constant = integral_constant<bool, B>;

    typedef bool_constant<true> true_type;
    typedef bool_constant<false> false_type;

    template <typename T> 
    struct is_reference : CustomStd::false_type {};

    template <typename T> 
    struct is_reference<T&> : CustomStd::true_type {};

    template <typename T> 
    struct is_reference<T&&> : CustomStd::true_type {};
    
    template <typename T>
    inline constexpr bool is_reference_v = is_reference<T>::value;

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

    template <bool B, typename T, typename F>
    struct conditional { 
        using type = T;
    };

    template <typename T, typename F>
    struct conditional<false, T, F> {
        using type = F;
    };
}

#endif