//
//  ConditionalEvent.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 11/03/2018.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <functional>

#include "Array.hpp"

template<class SubscriberType, class ...Params>
class ConditionalEvent {
    
public:
    using EventCallbackType = std::function<void(Params...)>;
    using EventConditionType = std::function<bool(SubscriberType*, Params...)>;

private:

    struct Subscriber {
        SubscriberType* object = nullptr;
        EventCallbackType action;

        Subscriber(SubscriberType* object, EventCallbackType action) : object(object), action(action) { }
    };
    
    Array<Subscriber> subscribers;
    
    EventConditionType _condition = [](SubscriberType*, Params...) { return true; };
    
public:
    
    ConditionalEvent() = default;

    ConditionalEvent(EventConditionType condition) : _condition(condition) { }
    
    void subscribe(SubscriberType* subscriber, EventCallbackType action) {
        subscribers.emplace_back(subscriber, action);
    }
    
    void unsubscribe(SubscriberType* subscriber) {
        subscribers.removeIf([&](SubscriberType* _sub) { return _sub == subscriber; });
    }
    
    void operator()(Params... parameters) const {
        for (const auto& subscriber : subscribers) {
            if (_condition(subscriber.object, parameters...))
                subscriber.action(parameters...);
        }
    }
};
