#include <charconv>
#include <string>

namespace css {

template <typename T, char const* unit_>
class unit_based_value {
public:
    unit_based_value(std::string const& value)
    {
        std::from_chars(value.data(), value.data() + value.size(), _numeric);
        _value = std::move(value);
    }

    bool operator==(unit_based_value const& nwu) const{ return _value == nwu._value; };
    bool operator!=(unit_based_value const& nwu) const { return _value != nwu._value; };

    T numeric() const { return _numeric; }
    std::string const& value() const { return _value; }
    std::string to_string() const { return _value + _unit; }

private:
    std::string _value;
    char const* const _unit = unit_;

    T _numeric; // just for optimized access
};

}
