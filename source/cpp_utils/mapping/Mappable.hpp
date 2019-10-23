//
//  Mappable.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 8/28/2019.
//  Copyright © 2019 VladasZ. All rights reserved.
//

#pragma once

#include <iostream>

#include "Log.hpp"
#include "Value.hpp"
#include "Property.hpp"
#include "IterateTuple.hpp"

#define _TEMPLATE template

namespace mapping {

	using ID = int;

    template<class Type>
    static constexpr bool is_supported =
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

		static const inline std::string id_key = "id";

		ID id = -1;

    protected:

        template<class Prop, class Member = typename Prop::Member>
        const Member& _value(const Prop& property) const {
            return dynamic_cast<const T*>(this)->*property.pointer;
        }

        template<class Prop, class Member = typename Prop::Member>
        void _set_value(const Prop& property, const Member& value) {
			if constexpr (Prop::is_string) {
				Value::check_string(value);
			}
			dynamic_cast<T*>(this)->*property.pointer = value;
		}

    public:

        template<class Field>
        Field get(const std::string& name) const { static_assert(is_supported<Field> || std::is_same_v<Field, Value>);

            if (name.empty()) {
                throw std::runtime_error("Field get::No property name for class " + T::class_name());
            }

			if (name == "id") {
				return id;
			}

            Value result;
            bool found = false;
            T::iterate_properties([&](auto property) {
                if (found) return;
                if (property.name == name) {
                    found = true;
					result = this->_value(property);
				}
            });

            if (!found) {
                throw std::runtime_error("Field get::No property: " + name + " in class " + T::class_name());
            }

            return result;
        }

		template<class Field>
		void set(const std::string& name, const Field& value) { static_assert(is_supported<Field> || std::is_same_v<Field, Value>);

			if (name.empty()) {
				throw std::runtime_error("Field set::No property name for class " + T::class_name());
			}

			if (name == "id") {
				id = value;
				return;
			}

			Value val = value;

			bool found = false;
			T::iterate_properties([&](auto property) {
			    using Member = typename decltype(property)::Member;
                if (found) return;
				if (property.name == name) {
					found = true;
					this->_set_value(property, val.convert<Member>());
				}
			});

            if (!found) {
				throw std::runtime_error("Field get::No property: " + name + " in class " + T::class_name());
			}
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

		void update_with(const T& other) {
			T::iterate_properties([&](auto property) {
				using Member = typename decltype(property)::Member;
				const auto value = other._value(property);
				if (value != Member { })
				    this->_set_value(property, value);
            });
		}

		Value unique_value() const {
			return get<Value>(T::unique_key);
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

		static inline const std::string unique_key = [] {
			std::string result;
			Mappable<T>::iterate_properties([&](auto property) {
				if (property.is_unique) 
					result = property.name;
			});
			return result;
		}();

		public:

			bool has_id() const {
				return id != -1;
			}

			bool has_unique_value() const {
			    return !unique_value().is_empty();
			}

    };

}
