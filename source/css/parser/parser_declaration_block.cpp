#include "context.h"
#include "parser.h"

namespace css::parser {

namespace {

    typedef bool (*attribute_parser)(context&, declaration_block&);

    template <style_id id>
    attribute_parser make_parser()
    {
        return [](context& context, declaration_block& block) {
            using value_type_t = typename style_typedef<id>::type_t;
            value_type_t value;
            if (!parser<value_type_t>::parse(context, value))
                return false;
            block.push_back<id>(std::move(value));
            return true;
        };
    }

    auto attribute_parser_list = std::unordered_map<std::string, attribute_parser> {
        { enum_table<style_id>[style_id::position], make_parser<style_id::position>() }
    };

}

bool parser<declaration_block>::has_matching_precondition(context& context)
{
    return context.peek().string_view() == "{";
}

bool parser<declaration_block>::parse(context& context, declaration_block& block)
{
    context.demand('{');
    context.consume(skip_trailing_whitespace);
    while (context.peek().type == token_type::ident) {
        auto style_name = context.peek().string();
        auto it = attribute_parser_list.find(style_name);
        if (it == attribute_parser_list.end())
            throw("skipping unknown attributes not implemented yet");
        auto& attribute_parser = it->second;
        context.consume(skip_trailing_whitespace);

        context.demand(':');
        context.consume(skip_trailing_whitespace);

        if (!attribute_parser(context, block))
            return false;

        if (context.peek().string_view() == "}")
            break;

        context.demand(';');
        context.consume(skip_trailing_whitespace);
    }
    context.demand('}');
    context.consume(skip_trailing_whitespace);
    return true;
}

}