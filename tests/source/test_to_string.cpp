#include <catch2/catch.hpp>

#include <css/model/model.h>
#include <css/model/to_string.h>

namespace {

inline bool ends_with(std::string const& s, std::string const& tail)
{
    if (tail.size() > s.size())
        return false;
    return std::equal(tail.rbegin(), tail.rend(), s.rbegin());
}

inline bool starts_with(std::string const& s, std::string const& head)
{
    return s.rfind(head, 0) == 0;
}

}

namespace css::test {

TEST_CASE("can stringify integer", "[to_string]")
{
    REQUIRE(to_string(12) == "12");
}

TEST_CASE("can stringify std::string", "[to_string]")
{
    REQUIRE(to_string(std::string("12")) == "12");
}

TEST_CASE("can stringify variant", "[to_string]")
{
    {
        auto v = std::variant<float, std::string>(12.0f);
        REQUIRE(to_string(v) == to_string(12.f));
    }
    {
        auto v = std::variant<float, std::string>("x");
        REQUIRE(to_string(v) == "x");
    }
}

TEST_CASE("can stringify px", "[to_string]")
{
    auto s = to_string(12._px);
    REQUIRE(starts_with(s, "12"));
    REQUIRE(ends_with(s, "px"));
}

TEST_CASE("stringify preserves structure", "[to_string]")
{
    REQUIRE(to_string(12._px) == "12.px");
}

}