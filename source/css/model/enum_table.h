#pragma once

#include <string_view>
#include <unordered_map>

namespace css {

template <typename T>
class enum_meta {
public:
    enum_meta(std::unordered_map<T, std::string> type_to_string)
        : _type_to_string(std::move(type_to_string))
    {
        for (auto& [t, s] : _type_to_string)
            _string_to_type[s] = t;
    }

    std::string const& operator[](T value) { return _type_to_string[value]; }
    T const& operator[](std::string const& s) { return _string_to_type[s]; }

    bool contains(std::string const& s) const { return _string_to_type.count(s); }
    bool contains(T const& t) const { return _type_to_string.count(t); }

    using const_iterator = typename std::unordered_map<T, std::string>::const_iterator;
    const_iterator begin() const { return _type_to_string.begin(); }
    const_iterator end() const { return _type_to_string.end(); }
    std::size_t size() const { return _type_to_string.size(); }

private:
    // use bimap?
    std::unordered_map<T, std::string> _type_to_string;
    std::unordered_map<std::string, T> _string_to_type;
};

//
// others (to_string, the model, the style.. ) depend upon this here
template <typename T>
extern enum_meta<T> enum_table;

}
