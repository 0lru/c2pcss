#pragma once

#include <cstdint>
#include <iomanip>
#include <optional>
#include <sstream>
#include <string>
#include <unordered_map>

namespace css {

class color {
public:
    color() = default;
    color(color const&) = default;
    color(color&&) = default;

    // no explicit
    color(std::string const&);

    // no explicit
    color(std::uint32_t rgba);

    // no explicit
    color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha);

    color& operator=(color const&) = default;
    color& operator=(color&&) = default;

    bool operator==(color const&) const;

    std::uint8_t red() const;
    void set_red(std::uint8_t red) { _value  = (_value & 0x00FFFFFF) | (red << 24); }
    std::uint8_t green() const;
    void set_green(std::uint8_t green) { _value = (_value & 0xFF00FFFF) | (green << 16); }
    std::uint8_t blue() const;
    void set_blue(std::uint8_t blue) { _value = (_value & 0xFFFF00FF) | (blue << 8); }
    std::uint8_t alpha() const;
    void set_alpha(std::uint8_t alpha) { _value = (_value & 0xFFFFFF00) | (alpha << 0); }

    struct named;

    operator std::uint32_t() const;

    static color from_hex(std::string const&);
    static color from_string(std::string const& input);

private:
    std::uint32_t _value;
    static std::unordered_map<std::string, color const&> _lut;
};

namespace {
    inline color _from_hex(std::string const& input)
    {
        if (input.size() == 6)
            return static_cast<std::uint32_t>(stoul(input, nullptr, 16)) << 8 | 0xFF;
        if (input.size() == 8)
            return static_cast<std::uint32_t>(stoul(input, nullptr, 16));
        else if (input.size() == 3) {
            auto x = static_cast<std::uint32_t>(stoul(input, nullptr, 16));
            return ((x & 0x00F) << 4 | (x & 0x00F) << 0 | (x & 0x0F0) << 8 | (x & 0x0F0) << 4 | (x & 0xF00) << 12 | (x & 0xF00) << 8) << 8 | 0xFF;
        } else
            throw std::runtime_error("could not create color from \"" + input + "\"");
    }
}

inline color color::from_hex(std::string const& input)
{
    auto l = input.size();
    if (input.empty())
        return 0u;
    return _from_hex(input[0] == '#' ? input.substr(1) : input);
}

inline color color::from_string(std::string const& input)
{
    if (input.empty())
        return color();
    if (input[0] == '#')
        return from_hex(input);
    auto it = _lut.find(input);
    if (it != _lut.end())
        return it->second;
    throw std::runtime_error("failed to parse color \"" + input + "\"");
}

inline color::color(std::uint32_t rgba)
    : _value(rgba)
{
}

inline color::color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha)
{
    set_red(red);
    set_green(green);
    set_blue(blue);
    set_alpha(alpha);
}

inline color::color(std::string const& str)
{
    *this = from_string(str);
}

inline color::operator std::uint32_t() const
{
    return _value;
}

inline bool color::operator==(color const& color) const
{
    return _value == color._value;
}

inline std::uint8_t color::red() const
{
    return (_value & 0xFF000000) >> 24;
}

inline std::uint8_t color::green() const
{
    return (_value & 0x00FF0000) >> 16;
}

inline std::uint8_t color::blue() const
{
    return (_value & 0x0000FF00) >> 8;
}

inline std::uint8_t color::alpha() const
{
    return _value & 0x000000FF;
}

struct color::named {
    inline static const auto black = color(0x000000ff);
    inline static const auto silver = color(0xc0c0c0ff);
    inline static const auto gray = color(0x808080ff);
    inline static const auto white = color(0xffffffff);
    inline static const auto maroon = color(0x800000ff);
    inline static const auto red = color(0xff0000ff);
    inline static const auto purple = color(0x800080ff);
    inline static const auto fuchsia = color(0xff00ffff);
    inline static const auto green = color(0x008000ff);
    inline static const auto lime = color(0x00ff00ff);
    inline static const auto olive = color(0x808000ff);
    inline static const auto yellow = color(0xffff00ff);
    inline static const auto navy = color(0x000080ff);
    inline static const auto blue = color(0x0000ffff);
    inline static const auto teal = color(0x008080ff);
    inline static const auto aqua = color(0x00ffffff);
    inline static const auto orange = color(0xffa500ff);
    inline static const auto aliceblue = color(0xf0f8ffff);
    inline static const auto antiquewhite = color(0xfaebd7ff);
    inline static const auto aquamarine = color(0x7fffd4ff);
    inline static const auto azure = color(0xf0ffffff);
    inline static const auto beige = color(0xf5f5dcff);
    inline static const auto bisque = color(0xffe4c4ff);
    inline static const auto blanchedalmond = color(0xffe4c4ff);
    inline static const auto blueviolet = color(0x8a2be2ff);
    inline static const auto brown = color(0xa52a2aff);
    inline static const auto burlywood = color(0xdeb887ff);
    inline static const auto cadetblue = color(0x5f9ea0ff);
    inline static const auto chartreuse = color(0x7fff00ff);
    inline static const auto chocolate = color(0xd2691eff);
    inline static const auto coral = color(0xff7f50ff);
    inline static const auto cornflowerblue = color(0x6495edff);
    inline static const auto cornsilk = color(0xfff8dcff);
    inline static const auto crimson = color(0xdc143cff);
    inline static const auto darkblue = color(0x00008bff);
    inline static const auto darkcyan = color(0x008b8bff);
    inline static const auto darkgoldenrod = color(0xb8860bff);
    inline static const auto darkgray = color(0xa9a9a9ff);
    inline static const auto darkgreen = color(0x006400ff);
    inline static const auto darkgrey = color(0xa9a9a9ff);
    inline static const auto darkkhaki = color(0xbdb76bff);
    inline static const auto darkmagenta = color(0x8b008bff);
    inline static const auto darkolivegreen = color(0x556b2fff);
    inline static const auto darkorange = color(0xff8c00ff);
    inline static const auto darkorchid = color(0x9932ccff);
    inline static const auto darkred = color(0x8b0000ff);
    inline static const auto darksalmon = color(0xe9967aff);
    inline static const auto darkseagreen = color(0x8fbc8fff);
    inline static const auto darkslateblue = color(0x483d8bff);
    inline static const auto darkslategray = color(0x2f4f4fff);
    inline static const auto darkslategrey = color(0x2f4f4fff);
    inline static const auto darkturquoise = color(0x00ced1ff);
    inline static const auto darkviolet = color(0x9400d3ff);
    inline static const auto deeppink = color(0xff1493ff);
    inline static const auto deepskyblue = color(0x00bfffff);
    inline static const auto dimgray = color(0x696969ff);
    inline static const auto dimgrey = color(0x696969ff);
    inline static const auto dodgerblue = color(0x1e90ffff);
    inline static const auto firebrick = color(0xb22222ff);
    inline static const auto floralwhite = color(0xfffaf0ff);
    inline static const auto forestgreen = color(0x228b22ff);
    inline static const auto gainsboro = color(0xdcdcdcff);
    inline static const auto ghostwhite = color(0xf8f8ffff);
    inline static const auto gold = color(0xffd700ff);
    inline static const auto goldenrod = color(0xdaa520ff);
    inline static const auto greenyellow = color(0xadff2fff);
    inline static const auto grey = color(0x808080ff);
    inline static const auto honeydew = color(0xf0fff0ff);
    inline static const auto hotpink = color(0xff69b4ff);
    inline static const auto indianred = color(0xcd5c5cff);
    inline static const auto indigo = color(0x4b0082ff);
    inline static const auto ivory = color(0xfffff0ff);
    inline static const auto khaki = color(0xf0e68cff);
    inline static const auto lavender = color(0xe6e6faff);
    inline static const auto lavenderblush = color(0xfff0f5ff);
    inline static const auto lawngreen = color(0x7cfc00ff);
    inline static const auto lemonchiffon = color(0xfffacdff);
    inline static const auto lightblue = color(0xadd8e6ff);
    inline static const auto lightcoral = color(0xf08080ff);
    inline static const auto lightcyan = color(0xe0ffffff);
    inline static const auto lightgoldenrodyellow = color(0xfafad2ff);
    inline static const auto lightgray = color(0xd3d3d3ff);
    inline static const auto lightgreen = color(0x90ee90ff);
    inline static const auto lightgrey = color(0xd3d3d3ff);
    inline static const auto lightpink = color(0xffb6c1ff);
    inline static const auto lightsalmon = color(0xffa07aff);
    inline static const auto lightseagreen = color(0x20b2aaff);
    inline static const auto lightskyblue = color(0x87cefaff);
    inline static const auto lightslategray = color(0x778899ff);
    inline static const auto lightslategrey = color(0x778899ff);
    inline static const auto lightsteelblue = color(0xb0c4deff);
    inline static const auto lightyellow = color(0xffffe0ff);
    inline static const auto limegreen = color(0x32cd32ff);
    inline static const auto linen = color(0xfaf0e6ff);
    inline static const auto mediumaquamarine = color(0x66cdaaff);
    inline static const auto mediumblue = color(0x0000cdff);
    inline static const auto mediumorchid = color(0xba55d3ff);
    inline static const auto mediumpurple = color(0x9370dbff);
    inline static const auto mediumseagreen = color(0x3cb371ff);
    inline static const auto mediumslateblue = color(0x7b68eeff);
    inline static const auto mediumspringgreen = color(0x00fa9aff);
    inline static const auto mediumturquoise = color(0x48d1ccff);
    inline static const auto mediumvioletred = color(0xc71585ff);
    inline static const auto midnightblue = color(0x191970ff);
    inline static const auto mintcream = color(0xf5fffaff);
    inline static const auto mistyrose = color(0xffe4e1ff);
    inline static const auto moccasin = color(0xffe4b5ff);
    inline static const auto navajowhite = color(0xffdeadff);
    inline static const auto oldlace = color(0xfdf5e6ff);
    inline static const auto olivedrab = color(0x6b8e23ff);
    inline static const auto orangered = color(0xff4500ff);
    inline static const auto orchid = color(0xda70d6ff);
    inline static const auto palegoldenrod = color(0xeee8aaff);
    inline static const auto palegreen = color(0x98fb98ff);
    inline static const auto paleturquoise = color(0xafeeeeff);
    inline static const auto palevioletred = color(0xdb7093ff);
    inline static const auto papayawhip = color(0xffefd5ff);
    inline static const auto peachpuff = color(0xffdab9ff);
    inline static const auto peru = color(0xcd853fff);
    inline static const auto pink = color(0xffc0cbff);
    inline static const auto plum = color(0xdda0ddff);
    inline static const auto powderblue = color(0xb0e0e6ff);
    inline static const auto rosybrown = color(0xbc8f8fff);
    inline static const auto royalblue = color(0x4169e1ff);
    inline static const auto saddlebrown = color(0x8b4513ff);
    inline static const auto salmon = color(0xfa8072ff);
    inline static const auto sandybrown = color(0xf4a460ff);
    inline static const auto seagreen = color(0x2e8b57ff);
    inline static const auto seashell = color(0xfff5eeff);
    inline static const auto sienna = color(0xa0522dff);
    inline static const auto skyblue = color(0x87ceebff);
    inline static const auto slateblue = color(0x6a5acdff);
    inline static const auto slategray = color(0x708090ff);
    inline static const auto slategrey = color(0x708090ff);
    inline static const auto snow = color(0xfffafaff);
    inline static const auto springgreen = color(0x00ff7fff);
    inline static const auto steelblue = color(0x4682b4ff);
    inline static const auto tan = color(0xd2b48cff);
    inline static const auto thistle = color(0xd8bfd8ff);
    inline static const auto tomato = color(0xff6347ff);
    inline static const auto turquoise = color(0x40e0d0ff);
    inline static const auto violet = color(0xee82eeff);
    inline static const auto wheat = color(0xf5deb3ff);
    inline static const auto whitesmoke = color(0xf5f5f5ff);
    inline static const auto yellowgreen = color(0x9acd32ff);
    inline static const auto rebeccapurple = color(0x663399ff);
};

inline std::unordered_map<std::string, color const&> color::_lut = {
    { "black", color::named::black },
    { "silver", color::named::silver },
    { "gray", color::named::gray },
    { "white", color::named::white },
    { "maroon", color::named::maroon },
    { "red", color::named::red },
    { "purple", color::named::purple },
    { "fuchsia", color::named::fuchsia },
    { "green", color::named::green },
    { "lime", color::named::lime },
    { "olive", color::named::olive },
    { "yellow", color::named::yellow },
    { "navy", color::named::navy },
    { "blue", color::named::blue },
    { "teal", color::named::teal },
    { "aqua", color::named::aqua },
    { "orange", color::named::orange },
    { "aliceblue", color::named::aliceblue },
    { "antiquewhite", color::named::antiquewhite },
    { "aquamarine", color::named::aquamarine },
    { "azure", color::named::azure },
    { "beige", color::named::beige },
    { "bisque", color::named::bisque },
    { "blanchedalmond", color::named::blanchedalmond },
    { "blueviolet", color::named::blueviolet },
    { "brown", color::named::brown },
    { "burlywood", color::named::burlywood },
    { "cadetblue", color::named::cadetblue },
    { "chartreuse", color::named::chartreuse },
    { "chocolate", color::named::chocolate },
    { "coral", color::named::coral },
    { "cornflowerblue", color::named::cornflowerblue },
    { "cornsilk", color::named::cornsilk },
    { "crimson", color::named::crimson },
    { "darkblue", color::named::darkblue },
    { "darkcyan", color::named::darkcyan },
    { "darkgoldenrod", color::named::darkgoldenrod },
    { "darkgray", color::named::darkgray },
    { "darkgreen", color::named::darkgreen },
    { "darkgrey", color::named::darkgrey },
    { "darkkhaki", color::named::darkkhaki },
    { "darkmagenta", color::named::darkmagenta },
    { "darkolivegreen", color::named::darkolivegreen },
    { "darkorange", color::named::darkorange },
    { "darkorchid", color::named::darkorchid },
    { "darkred", color::named::darkred },
    { "darksalmon", color::named::darksalmon },
    { "darkseagreen", color::named::darkseagreen },
    { "darkslateblue", color::named::darkslateblue },
    { "darkslategray", color::named::darkslategray },
    { "darkslategrey", color::named::darkslategrey },
    { "darkturquoise", color::named::darkturquoise },
    { "darkviolet", color::named::darkviolet },
    { "deeppink", color::named::deeppink },
    { "deepskyblue", color::named::deepskyblue },
    { "dimgray", color::named::dimgray },
    { "dimgrey", color::named::dimgrey },
    { "dodgerblue", color::named::dodgerblue },
    { "firebrick", color::named::firebrick },
    { "floralwhite", color::named::floralwhite },
    { "forestgreen", color::named::forestgreen },
    { "gainsboro", color::named::gainsboro },
    { "ghostwhite", color::named::ghostwhite },
    { "gold", color::named::gold },
    { "goldenrod", color::named::goldenrod },
    { "greenyellow", color::named::greenyellow },
    { "grey", color::named::grey },
    { "honeydew", color::named::honeydew },
    { "hotpink", color::named::hotpink },
    { "indianred", color::named::indianred },
    { "indigo", color::named::indigo },
    { "ivory", color::named::ivory },
    { "khaki", color::named::khaki },
    { "lavender", color::named::lavender },
    { "lavenderblush", color::named::lavenderblush },
    { "lawngreen", color::named::lawngreen },
    { "lemonchiffon", color::named::lemonchiffon },
    { "lightblue", color::named::lightblue },
    { "lightcoral", color::named::lightcoral },
    { "lightcyan", color::named::lightcyan },
    { "lightgoldenrodyellow", color::named::lightgoldenrodyellow },
    { "lightgray", color::named::lightgray },
    { "lightgreen", color::named::lightgreen },
    { "lightgrey", color::named::lightgrey },
    { "lightpink", color::named::lightpink },
    { "lightsalmon", color::named::lightsalmon },
    { "lightseagreen", color::named::lightseagreen },
    { "lightskyblue", color::named::lightskyblue },
    { "lightslategray", color::named::lightslategray },
    { "lightslategrey", color::named::lightslategrey },
    { "lightsteelblue", color::named::lightsteelblue },
    { "lightyellow", color::named::lightyellow },
    { "limegreen", color::named::limegreen },
    { "linen", color::named::linen },
    { "mediumaquamarine", color::named::mediumaquamarine },
    { "mediumblue", color::named::mediumblue },
    { "mediumorchid", color::named::mediumorchid },
    { "mediumpurple", color::named::mediumpurple },
    { "mediumseagreen", color::named::mediumseagreen },
    { "mediumslateblue", color::named::mediumslateblue },
    { "mediumspringgreen", color::named::mediumspringgreen },
    { "mediumturquoise", color::named::mediumturquoise },
    { "mediumvioletred", color::named::mediumvioletred },
    { "midnightblue", color::named::midnightblue },
    { "mintcream", color::named::mintcream },
    { "mistyrose", color::named::mistyrose },
    { "moccasin", color::named::moccasin },
    { "navajowhite", color::named::navajowhite },
    { "oldlace", color::named::oldlace },
    { "olivedrab", color::named::olivedrab },
    { "orangered", color::named::orangered },
    { "orchid", color::named::orchid },
    { "palegoldenrod", color::named::palegoldenrod },
    { "palegreen", color::named::palegreen },
    { "paleturquoise", color::named::paleturquoise },
    { "palevioletred", color::named::palevioletred },
    { "papayawhip", color::named::papayawhip },
    { "peachpuff", color::named::peachpuff },
    { "peru", color::named::peru },
    { "pink", color::named::pink },
    { "plum", color::named::plum },
    { "powderblue", color::named::powderblue },
    { "rosybrown", color::named::rosybrown },
    { "royalblue", color::named::royalblue },
    { "saddlebrown", color::named::saddlebrown },
    { "salmon", color::named::salmon },
    { "sandybrown", color::named::sandybrown },
    { "seagreen", color::named::seagreen },
    { "seashell", color::named::seashell },
    { "sienna", color::named::sienna },
    { "skyblue", color::named::skyblue },
    { "slateblue", color::named::slateblue },
    { "slategray", color::named::slategray },
    { "slategrey", color::named::slategrey },
    { "snow", color::named::snow },
    { "springgreen", color::named::springgreen },
    { "steelblue", color::named::steelblue },
    { "tan", color::named::tan },
    { "thistle", color::named::thistle },
    { "tomato", color::named::tomato },
    { "turquoise", color::named::turquoise },
    { "violet", color::named::violet },
    { "wheat", color::named::wheat },
    { "whitesmoke", color::named::whitesmoke },
    { "yellowgreen", color::named::yellowgreen },
    { "rebeccapurple", color::named::rebeccapurple }
};

inline std::string to_string(color const& color)
{
    std::stringstream ss;
    ss << "0x"
       << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
       << static_cast<int>(color.red())
       << static_cast<int>(color.green())
       << static_cast<int>(color.blue())
       << static_cast<int>(color.alpha());
    return ss.str();
}

}
