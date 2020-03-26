//
// Created by 毛华伟 on 2020/3/26.
//

#ifndef RSOCKET_EXAMPLE_STRINGUTILS_H
#define RSOCKET_EXAMPLE_STRINGUTILS_H

#include <iostream>


// 路由metadata char* 工具类
class StringUtils {

public:
  static char *string_to_char_p(std::string str) {

    int str_length = str.length();

    const char *data = str.data();

    char *new_data = new char[str_length + 1];
    
    new_data[0] = str_length;
    
    for (int i = 1; i <=str_length; i++) {
      new_data[i] = data[i - 1];
    }
    return new_data;
  }
};

#endif // RSOCKET_EXAMPLE_STRINGUTILS_H
