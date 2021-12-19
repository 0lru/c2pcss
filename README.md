# c2pcss
CSS Parser based on https://drafts.csswg.org/css-syntax

# Tokenizer:
```cpp
auto tokens = css::tokenize(R"(
    div {
        color: red;
    }
)");
```

# Parser:

The parser uses a strongly typed AST. As an example, it can parse a rule like this:
```cpp
css::rule_set value;
css::parse(R"(

abc:hover {
    position: inherit;
    color: 'red'
} 

)", value);
```

Each item in the AST can be parsed individually. One could
parse a declaration block, without the selector list:
```cpp
css::declaration_block value;
css::parse(R"(

{
    position: inherit;
    color: 'red'
} 

)", value);
```

Or just a color:

```cpp
auto color = css::parse<color>("red");
```

The AST can be back stringified with a generic to_string method:
```cpp
std::string text = css::to_string(value);
```

However, the parser is WIP and (a lot of) attributes
are not supported yet :-).
