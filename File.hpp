//
//  File.hpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 9/26/17.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once

class File {

  size_t _size = 0;
  char*  _data = nullptr;

public:

  size_t size() const;
  char*  data() const;

  File() = default;
  File(const char* path);
  ~File();
};
