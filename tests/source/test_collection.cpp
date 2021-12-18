#include <catch2/catch.hpp>
#include <css/model/collection.h>

namespace css::test {

TEST_CASE("can store value", "[parser][selector]")
{
    collection<style> map;
    map.push_back<style::left>(10_px);
    REQUIRE(map.size() == 1);
    auto value = map.get<style::left>();
    REQUIRE(std::holds_alternative<length>(value));
    REQUIRE(std::holds_alternative<px>(std::get<length>(value)));
    REQUIRE(std::get<px>(std::get<length>(value)) == 10_px );
}

}
