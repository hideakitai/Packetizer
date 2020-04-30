#pragma once

#ifndef ARX_TYPE_TRAITS_H
#define ARX_TYPE_TRAITS_H

#include <stddef.h>
#include <type_traits>

namespace arx {

	template<typename T> struct remove_reference                  { typedef T type; };
	template<typename T> struct remove_reference<T&>              { typedef T type; };
	template<typename T> struct remove_reference<T&&>             { typedef T type; };

	template <class T> constexpr T&& forward(typename std::remove_reference<T>::type& t) noexcept{
		return static_cast<T&&>(t);
	}
	template <class T> constexpr T&& forward(typename std::remove_reference<T>::type&& t) noexcept{
		//static_assert(!std::is_lvalue_reference<T>::value, "Can not forward an rvalue as an lvalue.");
		return static_cast<T&&>(t);
	}


    template<typename T, T ...Ts>
    struct integer_sequence
    {
        using type = integer_sequence;
        using value_type = T;
        static constexpr size_t size() noexcept { return sizeof...(Ts); }
    };

    template <std::size_t ...Is>
    using index_sequence = integer_sequence<std::size_t, Is...>;


    // https://stackoverflow.com/questions/17424477/implementation-c14-make-integer-sequence

    template<typename S1, typename S2>
    struct concat_impl;

    template<std::size_t... I1, std::size_t... I2>
    struct concat_impl <index_sequence<I1...>, index_sequence<I2...>>
    : index_sequence<I1..., (sizeof...(I1) + I2)...> {};

    template<typename S1, typename S2>
    using concat = typename concat_impl<S1, S2>::type;

    template<std::size_t N>
    struct make_index_sequence_impl;

    template<std::size_t N>
    using make_index_sequence = typename make_index_sequence_impl<N>::type;

    template<std::size_t N>
    struct make_index_sequence_impl
    : concat<make_index_sequence <N/2>, make_index_sequence <N - N/2>> {};

    template<>
    struct make_index_sequence_impl <0> : index_sequence<>{};
    template<>
    struct make_index_sequence_impl <1> : index_sequence<0>{};


    // https://qiita.com/_EnumHack/items/92e6e135174f1f781dbb
    // without decltype(auto)

    template <typename T>
    using decay_t = typename std::decay<T>::type;

    template <class F, class Tuple, std::size_t... I>
    constexpr auto apply_impl(F&& f, Tuple&& t, index_sequence<I...>)
    -> decltype(f(std::get<I>(std::forward<Tuple>(t))...))
    {
        return f(std::get<I>(std::forward<Tuple>(t))...);
    }

    template <class F, class Tuple>
    constexpr auto apply(F&& f, Tuple&& t)
    -> decltype(apply_impl(
        std::forward<F>(f),
        std::forward<Tuple>(t),
        make_index_sequence<std::tuple_size<decay_t<Tuple>>::value>{}
    ))
    {
        return apply_impl(
            std::forward<F>(f),
            std::forward<Tuple>(t),
            make_index_sequence<std::tuple_size<decay_t<Tuple>>::value>()
        );
    }
}

#endif // ARX_TYPE_TRAITS_H
