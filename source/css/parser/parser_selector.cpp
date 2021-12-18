#include "context.h"
#include "parser.h"

namespace css::parser {

bool parser<compound_selector>::parse(context& context, compound_selector& model)
{
    if (context.match('*')) {
        model.type_selector = type_selector { context.peek().string() };
        context.consume(keep_trailing_whitespace);
    } else if (context.match(token_type::ident)) {
        model.type_selector = type_selector { context.peek().string() };
        context.consume(keep_trailing_whitespace);
    }
    while (true) {
        if (context.match(token_type::hash)) {
            model.hash_selectors.push_back(hash_selector { context.peek().string() });
            context.consume(keep_trailing_whitespace); // hash
        } else if (context.match('.')) {
            context.consume(keep_trailing_whitespace); // delimiter
            context.demand(token_type::ident);
            model.class_selectors.push_back(class_selector { context.peek().string() });
            context.consume(keep_trailing_whitespace); // ident
        } else if (context.match(':')) {
            context.consume(keep_trailing_whitespace); // delimiter
            context.demand(token_type::ident);
            model.pseudo_selectors.push_back({ context.peek().string() });
            context.consume(keep_trailing_whitespace); // ident
        } else {
            break;
        }
    }
    //
    // lexeme finished
    context.skip_whitespace();
    return model.type_selector
        || !model.class_selectors.empty()
        || !model.hash_selectors.empty()
        || !model.pseudo_selectors.empty();
}

bool parser<complex_selector>::parse(context& iterator, complex_selector& complex)
{
    if (iterator.match(
            token_type::ident, // type selector
            token_type::hash,
            '*',
            '.', // class
            ':', // pseudo
            '>', // combinator
            '+', // combinator
            '~', // combinator
            '*' // universal sel.
            )) {
        compound_selector compound;
        if (!parser<compound_selector, void>::parse(iterator, compound))
            return false;
        complex.push_back(std::move(compound));
    }
    while (iterator.match(
        token_type::ident, // type selector
        token_type::hash,
        '*',
        '.', // class
        ':', // pseudo
        '>', // combinator
        '+', // combinator
        '~', // combinator
        '*' // universal sel.
        )) {
        compound_selector compound;
        if (!parser<compound_selector, void>::parse(iterator, compound))
            return false;
        complex.push_back(std::move(compound));
    }
    return !complex.empty();
}

bool parser<selector_list>::parse(context& iterator, selector_list& selector_list)
{
    if (iterator.match(
            token_type::ident, // type selector
            token_type::hash,
            '*',
            '.', // class
            ':', // pseudo
            '>', // combinator
            '+', // combinator
            '~', // combinator
            '*' // universal sel. (which is no ident)
            )) {
        complex_selector complex;
        if (!parser<complex_selector, void>::parse(iterator, complex))
            return false;
        selector_list.push_back(std::move(complex));
    }
    while (iterator.match(',')) {
        iterator.consume(skip_trailing_whitespace);
        complex_selector complex;
        if (!parser<complex_selector, void>::parse(iterator, complex))
            return false;
        selector_list.push_back(std::move(complex));
    }
    return !selector_list.empty();
}

}
