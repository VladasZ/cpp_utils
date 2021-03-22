
#include <memory>
#include <iostream>
#include "nlohmann/json.hpp"

using namespace std;

#define DECLARE_PROPERTIES(...) static constexpr auto properties() { return std::make_tuple(__VA_ARGS__); }
#define MAKE_PROPERTY(type, name) Property<&type::name>(#name)

template <int First, int Last, class Lambda>
constexpr void static_for_range([[maybe_unused]] const Lambda& f) {
    if constexpr (First < Last) {
        f(std::integral_constant<int, First> { });
        static_for_range<First + 1, Last>(f);
    }
}

template <int Last, class Lambda>
constexpr void static_for([[maybe_unused]] const Lambda& f) {
    static_for_range<0, Last>(f);
}

template <class Tuple, class Lambda>
constexpr void iterate_tuple(const Tuple& tup, const Lambda& f) {
    static_for<std::tuple_size<Tuple>::value>([&](auto i) {
        f(std::get<i>(tup));
    });
}

using JSON = nlohmann::json;

template <auto _pointer_to_member>
struct Property {
    static constexpr auto pointer_to_member = _pointer_to_member;
    const std::string_view name;
    constexpr explicit Property(const std::string_view& name) : name(name) { }
    std::string name_string() const { return std::string(name); }
    template<class Target, class T>
    static constexpr auto get_value(const T* pointer) {
        return static_cast<const Target*>(pointer)->*pointer_to_member;
    }

    template<class Target, class T>
    static constexpr auto& get_reference(T* pointer) {
        return static_cast<Target*>(pointer)->*pointer_to_member;
    }
};

class Empty {
public:
    static constexpr auto properties    () { return std::make_tuple(); }
    static constexpr auto all_properties() { return std::make_tuple(); }
};

struct is_mappable_base { };
template <class T> constexpr bool is_mappable_v = std::is_base_of_v<is_mappable_base, T>;

template <class T, class Base = Empty>
struct Mappable : public Base, is_mappable_base {

    template <class Action>
    constexpr static void iterate_properties(Action action) {
        iterate_tuple(all_properties(), action);
    }

    static void print_properties() {
        iterate_properties([](auto property) {
            cout << property.name_string() << endl;
        });
    }

    void print_values() const {
        iterate_properties([this](auto property) {
            auto value = property.template get_value<T>(this);
            if constexpr (is_mappable_v<decltype(value)>) {
                value.print_values();
            }
            else {
                cout << property.name_string() << " : " << property.template get_value<T>(this) << endl;
            }
        });
    }

    static constexpr auto all_properties() {
        return std::tuple_cat(Base::all_properties(), T::properties());
    };
};

struct is_json_mappable_base { };
template <class T> constexpr bool is_json_mappable_v = std::is_base_of_v<is_json_mappable_base, T>;

template <class T, class Base = Empty>
struct JSONMappable : public Mappable<T, Base>, is_json_mappable_base {

    using Map = Mappable<T, Base>;

    JSON to_json() const {
        JSON json;
        Map::iterate_properties([&](auto property) {
            auto value = property.template get_value<T>(this);
            if constexpr (is_json_mappable_v<decltype(value)>) {
                json[property.name_string()] = value.to_json();
            }
            else {
                json[property.name_string()] = value;
            }
        });
        return json;
    }

    static T from_json(const std::string str) {
        JSON json = JSON::parse(str);
        T result;
        Map::iterate_properties([&](auto property) {
            auto& value = property.template get_reference<T>(&result);
            using Value = std::remove_reference_t<decltype(value)>;
            if constexpr (is_json_mappable_v<Value>) {
                value = Value::from_json(json[property.name_string()].dump());
            }
            else {
                value = json[property.name_string()].template get<Value>();
            }
        });
        return result;
    }

};

template <class T, class Base = Empty>
struct Summable : public Mappable<T, Base> {
    using Map = Mappable<T, Base>;
    constexpr int summ() const {
        int result = 0;
        Map::iterate_properties([&](auto property) {
            result += property.template get_value<T>(this);
        });
        return result;
    }
};

template <class T, class Base>
using TeslaMappable = JSONMappable<T, Base>;

class Base : public Mappable<Base> {
    int base_int = 100;
public:
    DECLARE_PROPERTIES(
            MAKE_PROPERTY(Base, base_int)
    );
};

class Nested : public JSONMappable<Nested> {
    int nested_int = 312321;
public:
    DECLARE_PROPERTIES(
            MAKE_PROPERTY(Nested, nested_int)
    );
};

class Child : public Mappable<Child, Base> {
    Nested nested;
    int child_int = 200;
public:
    DECLARE_PROPERTIES(
            MAKE_PROPERTY(Child, nested),
            MAKE_PROPERTY(Child, child_int)
    );
};

class GrandChild : public TeslaMappable<GrandChild, Child> {
    int grand_child_int = 300;
public:
    DECLARE_PROPERTIES(
            MAKE_PROPERTY(GrandChild, grand_child_int)
    );
};

class Summ : public Summable<Summ> {
public:
    int a = 0;
    int b = 0;
    constexpr Summ(int a, int b) : a(a), b(b) { }
    DECLARE_PROPERTIES(
            MAKE_PROPERTY(Summ, a),
            MAKE_PROPERTY(Summ, b)
    );
};

static_assert(Summ(5, 5).summ() == 10);

//https://godbolt.org/z/Tnhcjf

int main() {

    GrandChild::print_properties();

    cout << "=========" << endl;

    GrandChild a;

    a.print_values();

    cout << "=========" << endl;

    cout << a.to_json() << endl;

    string json = "{\n"
                  "    \"base_int\": 100,\n"
                  "    \"child_int\": 200,\n"
                  "    \"grand_child_int\": 300,\n"
                  "    \"nested\":{\"nested_int\":312321}"
                  "}";

    GrandChild parsed = GrandChild::from_json(json);
    cout << parsed.to_json() << endl;

    return 0;
}
