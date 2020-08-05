//
//  Event.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 7/15/2018.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <vector>
#include <cassert>
#include <functional>

#include "ArrayUtils.hpp"


namespace cu {

    template<class ...Params>
    class Event {

        using Callback = std::function<void(Params...)>;
        using This = Event<Params...>;

        struct ObjectSubscriber {
            void* object;
            Callback callback;
            ObjectSubscriber(void* o, Callback c) : object(o), callback(c) { }
        };

    private:

        static constexpr auto params_count = sizeof...(Params);
        static constexpr bool one_param = params_count == 1;

        std::vector<Callback> subscribers;
        std::vector<ObjectSubscriber> object_subscribers;
        std::vector<This*> linked_events;

    public:

        [[nodiscard]]
        Callback& subscribe(void* object) {
            assert(object != nullptr);
            object_subscribers.emplace_back(object, Callback());
            return object_subscribers.back().callback;
        }

        void unsubscribe(void* object) {
            cu::array::remove_where(object_subscribers, [&](const ObjectSubscriber& subscriber) {
                return subscriber.object == object;
            });
        }

        template <class T>
        void operator = (T& param) {
            static_assert(one_param);
            using FirstType = std::tuple_element_t<0, std::tuple<Params...>>;
            static_assert(std::is_same_v<T, FirstType>);
            subscribers.push_back([&](auto value) { param = value; });
        }

        void operator = (const Callback& callback) {
            subscribers.push_back(callback);
        }

        void link(This& event) {
            linked_events.push_back(&event);
        }

        void unlink(This& event) {
            cu::array::remove(linked_events, &event);
        }

        void operator()(Params... parameters) const {
            for (auto& subscriber : subscribers) {
                subscriber(parameters...);
            }
            for (auto& subscriber : object_subscribers) {
                subscriber.callback(parameters...);
            }
            for (auto event : linked_events) {
                event->operator()(parameters...);
            }
        }

    };

}
