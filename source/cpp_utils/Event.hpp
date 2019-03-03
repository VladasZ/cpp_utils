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
    using EventCallbackType = std::function<void(Params...)>;
    using EventType = Event<Params...>;
    
private:
    std::vector<EventCallbackType> subscribers;
    std::vector<EventType*> linked_events;

public:
    
    Event() = default;

    void subscribe(EventCallbackType action) {
        subscribers.push_back(action);
    }
    
    void link(EventType& event) {
        linked_events.push_back(&event);
    }
    
    void operator()(Params... parameters) const {
        for (const auto& subscriber : subscribers)
            subscriber(parameters...);
        for (const auto event : linked_events)
            event->operator()(parameters...);
    }
};


template<>
class Event<> {

public:

    using EventCallbackType = std::function<void()>;
    std::vector<EventCallbackType> subscribers;

    Event() = default;

    void subscribe(EventCallbackType action) { subscribers.emplace_back(action); }
    void operator()() const { for (const auto& subscriber : subscribers) subscriber(); }
};

