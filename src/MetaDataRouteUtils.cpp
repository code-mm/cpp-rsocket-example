//
// Created by 毛华伟 on 2020/3/26.
//

#include "MetaDataRouteUtils.h"

namespace bdlbsc
{
    char *MetaDataRouteUtils::string_to_char_p(std::string str)
    {

        int str_length = str.length();

        const char *data = str.data();

        char *new_data = new char[str_length + 1];

        new_data[0] = str_length;

        for (int i = 1; i <= str_length; i++) {
            new_data[i] = data[i - 1];
        }
        return new_data;
    }
} // namespace bdlbsc
