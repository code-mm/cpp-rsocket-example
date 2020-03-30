//
// Created by 毛华伟 on 2020/3/26.
//

#ifndef RSOCKET_EXAMPLE_METADATAROUTEUTILS_H
#define RSOCKET_EXAMPLE_METADATAROUTEUTILS_H

#include <iostream>

namespace bdlbsc
{

    // 路由metadata char* 工具类
    class MetaDataRouteUtils
    {
    public:
        static char *string_to_char_p(std::string str);
    };

} // namespace bdlbsc
#endif // RSOCKET_EXAMPLE_METADATAROUTEUTILS_H
