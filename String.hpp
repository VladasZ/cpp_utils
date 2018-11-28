//
//  String.hpp
//  cpp_utils
//
//  Created by Vladas Zakrevskis on 1/30/18.
//  Copyright © 2018 VladasZ. All rights reserved.
//

#pragma once

#include <string>
#include <type_traits>

template <class T>
auto __to_string(const T &value) {
  if constexpr      (std::is_same_v<T, char>       ) return std::string(1, value);
  else if constexpr (std::is_same_v<T, const char*>) return std::string(value);
  else if constexpr (std::is_same_v<T, std::string>) return value;
  else if constexpr (std::is_fundamental_v<T>      ) return std::to_string(value);
}

class String : public std::string {
  
  using __str = std::string;
  
public:

  using __str::__str;

  String() = default;
  template<class T> String(const T &value) : __str(__to_string(value)) { }
  template<class T> String operator +  (const T &in) const { return (__str)*this + String(in); }
  template<class T> void   operator += (const T &in)       {                 this->append(in); }

  String file_name() const;
  
  static String from_float(float val, int precision = 2);
};

static String operator "" _s(const char* in, size_t size) { return String(in); };
static String operator "" _s(unsigned long long       in) { return String(in); };

