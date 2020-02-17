
#pragma once

#include <string>
#include <functional>

namespace cu {

template <class T>
class XYZPack {

  public:

    using ValueType = T;

    T x;
    T y;
    T z;

    XYZPack() = default;
    XYZPack(const T& value) : x(value), y(value), z(value) { }
    XYZPack(const T& x, const T& y, const T& z) : x(x), y(y), z(z) { }

    XYZPack& operator = (const T& value) {
        x = value;
        y = value;
        z = value;
        return *this;
    }

    T* begin() { return &x; }
    T* end()   { return &z + 1; }

    void apply(std::function<void(T&)> action) {
        action(x); action(y); action(z);
    }

    XYZPack& operator = (std::function<void(T&)> action) {
        apply(action);
        return *this;
    }

    std::string to_string() const {
        return std::string() + "\n"
                "X: " + x.to_string() + "\n" +
                "Y: " + y.to_string() + "\n" +
                "Z: " + z.to_string() + "\n";
    }
};

}
