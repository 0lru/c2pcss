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

The parser uses a strongly typed model. As an example, it can parse a rule like this:
```cpp
css::rule_set value;
css::parse(R"(

abc:hover {
    position: inherit;
    color: 'red'
} 

)", value);
```

Each item of the model can be parsed individually. One could also parse a declaration block without the selector list:
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
auto color = css::parse<css::color>("red");
```

Parsed items can be converted back to string with a generic to_string method:
```cpp
std::string text = css::to_string(value);
```

The parser is WIP and some (a lot of) attributes
are not supported yet :-).
