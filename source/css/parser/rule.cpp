#include "rule.h"

namespace css {

void rule<compound_selector, void>::apply_to(token_stream_reader& reader, compound_selector& model)
{
    if (reader.match_any_of(token_type::ident)) {
        model.type_selector = type_selector { reader.consume(token_type::ident, false).string() };
    }
    while (true) {
        if (reader.match_any_of(token_type::hash)) {

            model.hash_selectors.push_back({ reader.consume(token_type::hash, false).string() });

        } else if (reader.match_any_of('.')) {

            reader.consume(token_type::delimiter);
            model.class_selectors.push_back({ reader.consume(token_type::ident, false).string() });

        } else if (reader.match_any_of(':')) {

            reader.consume(token_type::delimiter);
            model.pseudo_selectors.push_back({ reader.consume(token_type::ident, false).string() });

        } else {
            break;
        }
    }
    //
    // lexeme finished
    reader.skip_whitespace();
}

void rule<complex_selector, void>::apply_to(token_stream_reader& reader, complex_selector& complex)
{
    if (reader.match_any_of(
            '.', // class
            ':', // pseudo
            '>', // combinator
            '+', // combinator
            '~', // combinator
            '*', // universal sel.
            token_type::ident, // type selector
            token_type::hash)) {
        compound_selector compound;
        rule<compound_selector, void>::apply_to(reader, compound);
        complex.push_back(std::move(compound));
    }
    while (reader.match_any_of(
        '.', // class
        ':', // pseudo
        '>', // combinator
        '+', // combinator
        '~', // combinator
        '*', // universal sel.
        token_type::ident, // type selector
        token_type::hash)) {
        compound_selector compound;
        rule<compound_selector, void>::apply_to(reader, compound);
        complex.push_back(std::move(compound));
    }
}

void rule<selector_list, void>::apply_to(token_stream_reader& reader, selector_list& selector_list)
{
    if (reader.match_any_of(
            '.', // class
            ':', // pseudo
            '>', // combinator
            '+', // combinator
            '~', // combinator
            '*', // universal sel.
            token_type::ident, // type selector
            token_type::hash)) {
        complex_selector complex;
        rule<complex_selector, void>::apply_to(reader, complex);
        selector_list.push_back(std::move(complex));
    }
    while (reader.match_any_of(',')) {
        reader.consume(token_type::delimiter);
        complex_selector complex;
        rule<complex_selector, void>::apply_to(reader, complex);
        selector_list.push_back(std::move(complex));
    }
}

}