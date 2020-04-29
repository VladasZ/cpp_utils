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

        void operator = (Callback action) {
            subscribers.push_back(action);
        }

        void link(This& event) {
            linked_events.push_back(&event);
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
