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

        static constexpr auto params_count = sizeof...(Params);
        static constexpr bool one_param = params_count == 1;

        std::vector<Callback> subscribers;
        std::vector<ObjectSubscriber> object_subscribers;

    public:

        [[nodiscard]]
        Callback& subscribe(void* object) {
            assert(object != nullptr);
            object_subscribers.emplace_back(object, Callback());
            return object_subscribers.back().callback;
        }

        void unsubscribe(void* object) {
            cu::container::remove_where(object_subscribers, [&](const ObjectSubscriber& subscriber) {
                return subscriber.object == object;
            });
        }

        void operator = (const Callback& callback) {
            subscribers.push_back(callback);
        }

        void operator()(Params... parameters) const {
            for (auto& subscriber : subscribers) {
                subscriber(parameters...);
            }
            for (auto& subscriber : object_subscribers) {
                subscriber.callback(parameters...);
            }
        }

    };

}
