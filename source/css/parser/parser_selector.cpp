#include "parser.h"

namespace css::parser {

void parser<compound_selector>::parse(input& iterator, compound_selector& model)
{
    if (iterator.match_any_of(token_type::ident)) {
        model.type_selector = type_selector { iterator.consume(token_type::ident, false).string() };
    }
    while (true) {
        if (iterator.match_any_of(token_type::hash)) {

            model.hash_selectors.push_back({ iterator.consume(token_type::hash, false).string() });

        } else if (iterator.match_any_of('.')) {

            iterator.consume(token_type::delimiter);
            model.class_selectors.push_back({ iterator.consume(token_type::ident, false).string() });

        } else if (iterator.match_any_of(':')) {

            iterator.consume(token_type::delimiter);
            model.pseudo_selectors.push_back({ iterator.consume(token_type::ident, false).string() });

        } else {
            break;
        }
    }
    //
    // lexeme finished
    iterator.skip_whitespace();
}

void parser<complex_selector>::parse(input& iterator, complex_selector& complex)
{
    if (iterator.match_any_of(
            token_type::ident, // type selector
            token_type::hash,
            '.', // class
            ':', // pseudo
            '>', // combinator
            '+', // combinator
            '~', // combinator
            '*' // universal sel.
            )) {
        compound_selector compound;
        parser<compound_selector, void>::parse(iterator, compound);
        complex.push_back(std::move(compound));
    }
    while (iterator.match_any_of(
        token_type::ident, // type selector
        token_type::hash,
        '.', // class
        ':', // pseudo
        '>', // combinator
        '+', // combinator
        '~', // combinator
        '*' // universal sel.
        )) {
        compound_selector compound;
        parser<compound_selector, void>::parse(iterator, compound);
        complex.push_back(std::move(compound));
    }
}

void parser<selector_list>::parse(input& iterator, selector_list& selector_list)
{
    if (iterator.match_any_of(
            token_type::ident, // type selector
            token_type::hash,
            '.', // class
            ':', // pseudo
            '>', // combinator
            '+', // combinator
            '~', // combinator
            '*' // universal sel. (which is no ident)
            )) {
        complex_selector complex;
        parser<complex_selector, void>::parse(iterator, complex);
        selector_list.push_back(std::move(complex));
    }
    while (iterator.match_any_of(',')) {
        iterator.consume(token_type::delimiter);
        complex_selector complex;
        parser<complex_selector, void>::parse(iterator, complex);
        selector_list.push_back(std::move(complex));
    }
}

}
