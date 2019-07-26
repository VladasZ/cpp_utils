//
//  Event.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 7/15/2018.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <vector>
#include <functional>

template<class ...Params>
class Event {
    
public:
    using Callback = std::function<void(Params...)>;
    using This = Event<Params...>;
    
private:
    std::vector<Callback> subscribers;
    std::vector<This*> linked_events;

public:
    
    Event() = default;

    void subscribe(Callback action) {
        subscribers.push_back(action);
    }
    
    void link(This& event) {
        linked_events.push_back(&event);
    }
    
    void operator()(Params... parameters) const {
        for (const auto& subscriber : subscribers)
            subscriber(parameters...);
        for (const auto event : linked_events)
            event->operator()(parameters...);
    }
};
