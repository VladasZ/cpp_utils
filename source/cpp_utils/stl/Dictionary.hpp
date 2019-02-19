//
//  Dictionary.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 6/25/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <map>

template <class Key, class Value>
class Dictionary : public std::map<Key, Value> {
    using __dictionary = std::map<Key, Value>;
public:
    using __dictionary::__dictionary;
};
