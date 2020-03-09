//
//  SignalGenerator.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 09/03/20.
//  Copyright © 2020 VladasZ. All rights reserved.
//

#pragma once

namespace cu {

    template <class T>
    class SignalGenerator {

    private:

        T _min;
        T _max;
        T _step;
        T _value;
        bool _up;

    public:

        SignalGenerator(T min, T max, T step = 1) : _min(min), _max(max), _step(step), _value(min), _up(true) { }

        T value() {
            if (_up) {
                _value += _step;
                if (_value >= _max) {
                    _value = _max;
                    _up = false;
                }
                return _value;
            }
            _value -= _step;
            if (_value <= _min) {
                _value = _min;
                _up = true;
            }
            return _value;
        }

    };

}
