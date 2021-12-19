#pragma once

#include "enum_table.h"

#include <string>
#include <type_traits>
#include <variant>

namespace css {

template <typename T, typename U = void>
struct to_string_ {
    inline static std::string impl(T const& value)
    {
        return std::to_string(value);
    }
};

//
// id should work in std also.. weird
template <>
struct to_string_<std::string> {
    inline static std::string impl(std::string const& value)
    {
        return value;
    }
};

//
// support classes that implement a to_string-method
template <typename T>
struct to_string_<T, typename std::enable_if<std::is_same<decltype(std::declval<T>().to_string()), std::string>::value>::type> {
    inline static std::string impl(T const& value)
    {
        return value.to_string();
    }
};

//
// per default stringify the "active" option of a variant
template <std::size_t I>
using index_t = std::integral_constant<std::size_t, I>;

template <std::size_t I>
constexpr index_t<I> index {};

template <std::size_t... Is>
constexpr std::tuple<index_t<Is>...> make_indexes(std::index_sequence<Is...>)
{
    return std::make_tuple(index<Is>...);
}

template <std::size_t N>
constexpr auto indexing_tuple = make_indexes(std::make_index_sequence<N> {});

template <std::size_t... Is, class T, class F>
auto tuple_foreach(std::index_sequence<Is...>, T&& tup, F&& f)
{
    (f(std::get<Is>(std::forward<T>(tup))), ...);
}

template <class T, class F>
auto tuple_foreach(T&& tup, F&& f)
{
    auto indexes = std::make_index_sequence<std::tuple_size_v<std::decay_t<T>>> {};
    return tuple_foreach(indexes, std::forward<T>(tup), std::forward<F>(f));
}

//
//
template <typename... Args>
struct to_string_<std::variant<Args...>> {
    inline static std::string impl(std::variant<Args...> const& v)
    {
        auto indexes = indexing_tuple<sizeof...(Args)>;
        std::optional<std::string> retval;
        tuple_foreach(indexes, [&](auto I) {
            using current_t = std::variant_alternative_t<I, std::variant<Args...>>;
            if (std::holds_alternative<current_t>(v))
                retval = to_string(std::get<current_t>(v));
        });
        return retval ? retval.value() : std::string();
    }
};

//
// enumerations

template <typename T>
struct to_string_<T, typename std::enable_if<std::is_enum<T>::value>::type> {
    inline static std::string impl(T const& value)
    {
        return enum_table<T>[value];
    }
};

template <typename T>
struct to_string_<T const, typename std::enable_if<std::is_enum<T>::value>::type> {
    inline static std::string impl(T const& value)
    {
        return enum_table<T>[value];
    }
};

//
// convenience function
template <typename T>
std::string to_string(T const& value) { return to_string_<T>::impl(value); }

}
