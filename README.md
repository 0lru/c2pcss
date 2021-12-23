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

The parser only provides models for very basic types, like colors or lengths. This is because
parsing strongly depends upon the underlying implementation. 

```cpp
auto color = css::parse<css::color>("red");
```

Parsed items can be converted back to string with a generic to_string method:
```cpp
std::string text = css::to_string(color);
```
