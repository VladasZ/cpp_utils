
#include <memory>

#include "Log.hpp"

class Foo {
private:
    void test() {
        Log << "Hello";
    }
};

template <class T, auto member_pointer>
struct RobMember {

    using Member = typename T::FunctionMember;

private:
    friend Member GetPrivateMember(T) {
        return member_pointer;
    }
};

struct Rob {
    using FunctionMember = void (Foo::*)();
private:
    friend FunctionMember GetPrivateMember(Rob);
};

template struct RobMember<Rob, &Foo::test>;


int main() {

    Foo foo;
    GetPrivateMember(Rob());
    auto member = GetPrivateMember(Rob());
    (foo.*member)();

    return 0;

}
