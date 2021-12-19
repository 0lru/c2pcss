#include <catch2/catch.hpp>
#include <css/model/model.h>

namespace css {

template <>
class style_typedef<style_id::left> {
public:
    using type_t = css::length_percentage;
};

}

namespace css::test {

TEST_CASE("can store value", "[parser][selector]")
{
    collection<style_id, style_typedef> map;
    map.push_back<style_id::left>(10_px);
    REQUIRE(map.size() == 1);
    auto value = map.get<style_id::left>();
    REQUIRE(std::holds_alternative<length>(value));
    REQUIRE(std::holds_alternative<px>(std::get<length>(value)));
    REQUIRE(std::get<px>(std::get<length>(value)) == 10_px);
}

}
