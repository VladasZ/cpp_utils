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
            bool operator ==(const ObjectSubscriber& other) const {
                return object == other.object;
            }
        };

    private:
        bool active = false;
        std::vector<Callback> subscribers;
        std::vector<ObjectSubscriber> object_subscribers;
    public:

        Event() = default;

        [[nodiscard]]
        Callback& subscribe(void* object) {
            active = true;
            assert(object != nullptr);
            object_subscribers.emplace_back(object, Callback());
            return object_subscribers.back().callback;
        }

        void unsubscribe(void* object) {
            cu::array::remove_where(object_subscribers, [&](const ObjectSubscriber& subscriber) {
                return subscriber.object == object;
            });
            if (subscribers.empty() && object_subscribers.empty()) {
                active = false;
            }
        }

        void operator = (Callback action) {
            active = true;
            subscribers.push_back(action);
        }

        void operator()(Params... parameters) const {
            if (!active) return;
            for (auto subscriber : subscribers) {
                subscriber(parameters...);
            }
            for (auto& subscriber : object_subscribers) {
                subscriber.callback(parameters...);
            }
        }
    };

}
