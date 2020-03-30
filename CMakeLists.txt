cmake_minimum_required(VERSION 3.15)
project(rsocket_example)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CURRENT_SOURCE_DIR ON)

include_directories(/usr/local/dev/vcpkg/installed/x64-osx/include)
link_directories(/usr/local/dev/vcpkg/installed/x64-osx/lib)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)


find_package(folly CONFIG REQUIRED)
find_package(yarpl REQUIRED)
find_package(rsocket REQUIRED)

add_executable(
        rsocket_example
        src/main.cpp
        src/MetaDataRouteUtils.cpp
        src/MetaDataRouteUtils.h
        src/AppRSocketClient.cpp
        src/AppRSocketClient.h)
target_link_libraries(${PROJECT_NAME} PRIVATE yarpl)
target_link_libraries(${PROJECT_NAME} PRIVATE ReactiveSocket)
target_link_libraries(${PROJECT_NAME} PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark)