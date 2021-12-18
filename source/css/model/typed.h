namespace css {

//
// a typedef is not expedient. using this as pain relief.
template <typename T>
struct typed {
    typed() = default;
    typed(T&& t) { value = std::move(t); }
    typed(T const&) { value = t; }

    typed& operator=(T&& t) { value = std::move(t); }
    typed& operator=(T const& t) { value = t; }

    bool operator==(T const& t) const{ return t == value; }
    bool operator!=(T const& t) const{ return t != value; }

    operator T() const { return value; }
    operator T&() { return value; }
    operator T const &() const { return value; }

    std::string value;
};

}