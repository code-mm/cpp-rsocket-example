//
// Created by 毛华伟 on 2020/3/30.
//

#ifndef RSOCKET_EXAMPLE_APPRSOCKETCLIENT_H
#define RSOCKET_EXAMPLE_APPRSOCKETCLIENT_H

#include <folly/init/Init.h>
#include <folly/io/async/ScopedEventBaseThread.h>
#include <folly/portability/GFlags.h>
#include <yarpl/Flowable.h>
#include <yarpl/Single.h>

#include <rsocket/RSocket.h>
#include <rsocket/RSocketClient.h>
#include <rsocket/transports/tcp/TcpConnectionFactory.h>

#include <iostream>

namespace bdlbsc
{
    class AppRSocketClient
    {

    public:
        AppRSocketClient(std::string host, int port);
        ~AppRSocketClient();

        // 连接
        void connect();
        // 从新连接
        void re_connect();
        // 断开连接
        void disconnect();
        
        const std::unique_ptr<rsocket::RSocketClient> &get_client() const;

        // 是否连接上
        bool _open = false;

        // 开始连接
        bool _start = false;

    private:
        // 连接客户端
        std::unique_ptr<rsocket::RSocketClient> _client;
        // 连接地址
        folly::SocketAddress _address;
        // 线程
        folly::ScopedEventBaseThread _worker;
        // 状态
        std::shared_ptr<rsocket::RSocketStats> _stats = rsocket::RSocketStats::noop();
        // 连接管理器
        folly::EventBase *_connect_event_base;
        //
        folly::EventBase *_app_client_event_base;

    public:
        folly::EventBase *get_connect_event_base() const;
        folly::EventBase *get_app_client_event_base() const;

    private:
        // 主机
        std::string _host;
        // 端口
        int _port;

    public:
        const std::shared_ptr<rsocket::RSocketStats> &get_stats() const;
    };

    class ConnectionEvents : public rsocket::RSocketConnectionEvents
    {

    public:
        ConnectionEvents(AppRSocketClient *app_rsocket_client);
        ~ConnectionEvents();

        void onConnected();

        void onDisconnected(const folly::exception_wrapper &e);
        void onClosed(const folly::exception_wrapper &e);
        void onStreamsPaused();
        void onStreamsResumed();

    private:
        AppRSocketClient *_app_rsocket_client;
    };

} // namespace bdlbsc
#endif // RSOCKET_EXAMPLE_APPRSOCKETCLIENT_H
