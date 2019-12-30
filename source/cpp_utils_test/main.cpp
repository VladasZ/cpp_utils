
#include "Log.hpp"
#include "JSONMappable.hpp"

class TestClass : public mapping::JSONMappable<TestClass> {

public:

    int a = 10;
    std::string b = "10";

    static std::string class_name() {
        return "TestClass";
    }

    static auto properties() {
        return std::make_tuple(
                mapping::Property("a", &TestClass::a),
                mapping::Property("b", &TestClass::b)
        );
    }

};

int main() {
  Log(TestClass::parse(TestClass().to_json()).to_json());
}
