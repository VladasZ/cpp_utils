//
//  Event.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 7/15/2018.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <functional>

#include "Array.hpp"

template<class ...Params>
class Event {
    
public:
    using EventCallbackType = std::function<void(Params...)>;
    using EventType = Event<Params...>;
    
private:
    Array<EventCallbackType> subscribers;
    Array<EventType*> linkedEvents;

public:
    
    Event() = default;

    void subscribe(EventCallbackType action) {
        subscribers.push_back(action);
    }
    
    void link(EventType& event) {
        linkedEvents.push_back(&event);
    }
    
    void operator()(Params... parameters) const {
        for (const auto& subscriber : subscribers)
            subscriber(std::forward<Params ...>(parameters...));
        for (const auto event : linkedEvents)
            event->operator()(std::forward<Params ...>(parameters...));
    }
};


template<>
class Event<> {

public:

    using EventCallbackType = std::function<void()>;
    Array<EventCallbackType> subscribers;

    Event() = default;

    void subscribe(EventCallbackType action) { subscribers.emplace_back(action); }
    void operator()() const { for (const auto& subscriber : subscribers) subscriber(); }
};

