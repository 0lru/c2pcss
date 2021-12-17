#include <stdexcept>

namespace css {

class parser_error : public std::runtime_error {
public:
    parser_error(std::size_t line, std::size_t column, std::string const& what)
        : std::runtime_error(what)
        , _line(line)
        , _column(column)
    {
    }

    std::size_t line() const { return _line; }
    std::size_t column() const { return _column; }

private:
    std::size_t _line;
    std::size_t _column;
};

}