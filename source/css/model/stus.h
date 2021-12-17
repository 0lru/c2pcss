#include <unordered_map>
#include <memory>

// "strongly typed sparse storage"
template <typename EnumType, OrderType = std::uint16_t>
class stuss {
public:

    template<Id>
    get<Id>() -> TypeOf<EnumType> ....

private:
    template<typename T>
    struct entry
    {
        OrderType _order;
        std::unique_ptr<T> _value;
    };
    std::unordered_map<EnumType, > _sparse;
};

