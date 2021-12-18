#include "style.h"

#include <memory>
#include <unordered_map>

namespace css {

// "strongly typed sparse storage"
template <typename EnumType>
class collection {
public:
    /*    void set(Style identifier, std::shared_ptr<ComputedStyle const> style)
        {
            _set[identifier] = Entry{ std::move(style), _priority++ };
        }
        */

    template <style style_>
    void push_back(typename style_definition<style_>::type_t&& value)
    {
        using value_t = typename style_definition<style_>::type_t;
        auto item = std::unique_ptr<entry<value_t>>(
            new entry<value_t>(0, std::move(value)));
        _ordered.push_back(item.get());
        _map[style_] = std::move(item);
    }

    template<style style_>
    auto get() const -> typename style_definition<style_>::type_t const&
    {
        using value_t = typename style_definition<style_>::type_t;
        auto it = _map.find(style_);
        if (it != _map.end())
            return static_cast<entry<value_t> const&>(*it->second).value;
        throw std::runtime_error("no value present for \"" + to_string(style_) + "\"");
    }

    std::size_t size() const { return _ordered.size(); }

private:
    struct entry_ {
        std::uint16_t position;
    };
    template <typename T>
    struct entry : public entry_ {
        entry(std::uint16_t position, T&& value)
            : value(std::move(value))
        {
            this->position = position;
        }
        T value;
    };
    std::uint16_t _position;
    std::vector<entry_*> _ordered;
    std::unordered_map<EnumType, std::unique_ptr<entry_>> _map;
};

}