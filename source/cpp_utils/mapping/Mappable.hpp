//
//  Mappable.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/28/2019.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <iostream>

#include "Value.hpp"
#include "Property.hpp"
#include "IterateTuple.hpp"

namespace mapping {

    template<class Type>
    static constexpr bool supported =
            std::is_same_v<Type, std::string> ||
            std::is_same_v<Type, int        > ||
            std::is_same_v<Type, float      >;

    template<class T> class Mappable;

    template <class Type>
    static constexpr bool is_mappable = std::is_base_of<Mappable<Type>, Type>::value;

    template<class T>
    class Mappable {

    public:

        using This = T;

    protected:

        template<class Prop>
        auto _value(const Prop& property) const {
            return dynamic_cast<const T*>(this)->*property.pointer;
        }

    public:

        template<class Field>
        Field get(const std::string& name) const {
            static_assert(supported<Field> || std::is_same_v<Field, Value>,
                          "Type is not supported");

            if (name.empty()) {
                throw std::runtime_error("Field get::No property name for class " + T::class_name());
            }

            Value result;
            bool found = false;
            T::iterate_properties([&](auto property) {
                if (found) return;
                if (property.name == name) {
                    found = true;
					//result = this->template _value(property);
					result = this->_value(property);
				}
            });

            if (!found) {
                throw std::runtime_error("Field get::No property: " + name + " in class " + T::class_name());
            }

            return result;
        }

        std::string edited_field() const {
            std::string result;
            bool found = false;
            T::iterate_properties([&](auto property) {
                if (found) {
                    return;
                }
                if (_value(property) != typename decltype(property)::Member { }) {
                    result = property.name;
                    found = true;
                }
            });
            if (!found) {
                throw std::runtime_error("No edited field found in class " + T::class_name());
            }
            return result;
        }

        Value primary_value() const {
            return get<Value>(T::primary_key);
        }

        virtual std::string to_string() {
            return T::class_name();
        }

        template<class Closure>
        static void iterate_properties(Closure&& closure) {
            cu::iterate_tuple(This::properties(), closure);
        }

        static void print_properties() {
            T::iterate_properties([](auto property) {
                std::cout << property.to_string() << std::endl;
            });
        }

        static T empty() {
            T result;
            T::iterate_properties([&](auto property) {
                result.*property.pointer = typename decltype(property)::Member { };
            });
            return result;
        }

        static inline const std::string primary_key = []{
            std::string result;
            bool found = false;
			Mappable<T>::iterate_properties([&](auto property) {
                if (property.is_primary) {
                    if (found) {
                        throw std::runtime_error(
                                "Class " + T::class_name() + " has 2 or more primary keys: " +
                                result + " and " + property.name
                        );
                    }
                    result = property.name;
                    found = true;
                }
            });
            return result;
        }();

    };

}
