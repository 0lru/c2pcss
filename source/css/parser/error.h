#include <css/tokenizer/token.h>

#include <stdexcept>

namespace css::parser {

//
// parsing may continue, although an error has occurred. the 
// error information is saved to the context and the process
// tries to continue.
class error {
public:
    error(token& token, std::string const& what)
        : _token(token)
    {
    }

    css::token& token() const { return _token; }
    std::size_t line() const { return _token.line; }
    std::size_t column() const { return _token.column; }

private:
    css::token& _token;
};

}
