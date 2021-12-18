#include <catch2/catch.hpp>
#include <css/parse.h>

namespace css::test {

TEST_CASE("can parse type selector", "[parser][selector]")
{
    compound_selector compound_selector;
    parse("abc", compound_selector);
    REQUIRE(compound_selector.type_selector);
    REQUIRE(compound_selector.type_selector.value() == "abc");
}

TEST_CASE("can parse compound selector", "[parser][selector]")
{
    compound_selector compound_selector;
    parse("abc#a.b:hover", compound_selector);
    REQUIRE(compound_selector.type_selector);
    REQUIRE(compound_selector.type_selector.value() == "abc");
    REQUIRE(compound_selector.hash_selectors.size() == 1);
    REQUIRE(compound_selector.class_selectors.size() == 1);
    REQUIRE(compound_selector.pseudo_selectors.size() == 1);
}

TEST_CASE("can parse complex selector", "[parser][selector]")
{
    complex_selector complex;
    parse("foo abc#a.b:hover .bar", complex);
    REQUIRE(complex.size() == 3);
}

TEST_CASE("can parse selector list", "[parser][selector]")
{
    selector_list l;
    parse("foo abc  ,#a.b:hover .bar, abc :gh", l);
    REQUIRE(l.size() == 3);
}

TEST_CASE("can parse universal selector", "[parser][selector]")
{
    complex_selector l;
    parse("* *.aasd *:hover", l);
    REQUIRE(l.size() == 3);
}

}
