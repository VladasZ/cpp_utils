//
//  ConditionalEvent.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 11/03/2018.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <vector>
#include <functional>

template<class Object, class ...Params>
class ConditionalEvent {
    
public:
    using Callback = std::function<void(Params...)>;
    using Condition = std::function<bool(SubscriberType*, Params...)>;

private:

    struct Container {
        Object* object;
        Callback action;
        Container(Object* object, Callback action) : object(object), action(action) { }
    };
    
    std::vector<Container> subscribers;
    
    Condition _condition;
    
public:
    
    ConditionalEvent(Condition condition) : _condition(condition) { }
    
    void subscribe(Object* subscriber, Callback action) {
        subscribers.emplace_back(subscriber, action);
    }
    
    void unsubscribe(Object* subscriber) {
        subscribers.remove_if([&](Container* _sub) { return _sub.object == subscriber; });
    }
    
    void operator()(Params... parameters) const {
        for (const auto& subscriber : subscribers) {
            if (_condition(subscriber.object, parameters...))
                subscriber.action(parameters...);
        }
    }
};
