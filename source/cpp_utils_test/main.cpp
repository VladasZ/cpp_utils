
#include <tuple>

#include "Log.hpp"

//
//template <class T>
//static constexpr auto check(const T& a) { // Checker that should be static
//    return a > 0;
//}
//
//template <class T>
//static constexpr bool test(const T a) { // Function to test it, works fine
//    static_assert(check(a));
//    return check(a);
//}

//static_assert(check(10)); // Function result, works fine


//template <class T>
//struct Test {
//
//    const T classes_info;
//
//    constexpr Test(const T info) : classes_info(info) {
//        static_assert(_tuple_is_valid(info));
//    }
//
//    //MARK: - Tuple Check
//
//    template <class Type>
//    static constexpr void _check(bool& value, const Type& param) {
//        if (param > 10) {
//            value = true;
//        }
//    }
//
//    template <class Type>
//    static constexpr bool _tuple_is_valid(const Type& tuple) {
//        bool result = false;
//        std::apply([&](auto&&... args) {((
//                _check(result, args)
//        ), ...);}, tuple);
//        return result;
//    }
//
//};

constexpr auto t = Test(std::tuple(1, 10));

int main() {

    //static_assert(only_int(tup));
}
