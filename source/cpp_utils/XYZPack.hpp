
#pragma once

#include <string>

namespace cu {

template <class T>
class XYZPack {

  public:

    T x;
    T y;
    T z;

    XYZPack() = default;
    XYZPack(const T& value) : x(value), y(value), z(value) { }
    XYZPack(const T& x, const T& y, const T& z) : x(x), y(y), z(z) { }

    template<class Value>
    XYZPack<T>& operator = (const Value& value) {
        x = value;
        y = value;
        z = value;
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
