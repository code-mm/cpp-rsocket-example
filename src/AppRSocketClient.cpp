//
// Created by 毛华伟 on 2020/3/30.
//

#include "AppRSocketClient.h"

namespace bdlbsc
{
    AppRSocketClient::AppRSocketClient(std::string host, int port)
    {
        this->_host = host;
        this->_port = port;
        _address.setFromHostPort(_host, port);
        _connect_event_base = _worker.getEventBase();
        _app_client_event_base = _worker.getEventBase();
        connect();
    }

    AppRSocketClient::~AppRSocketClient() {}

    void AppRSocketClient::connect()
    {
        _client = rsocket::RSocket::createConnectedClient(
                      std::make_unique<rsocket::TcpConnectionFactory>(*_connect_event_base->getEventBase(), std::move(_address)),
                      rsocket::SetupParameters("message/x.rsocket.routing.v0", "application/json"),
                      nullptr,
                      std::chrono::seconds(60 * 60),
                      _stats,
                      std::make_shared<ConnectionEvents>(this))
                      .get();
    }

    void AppRSocketClient::re_connect()
    {
        folly::makeFuture().via(_app_client_event_base->getEventBase()).delayed(std::chrono::seconds(10)).thenValue([this](auto &&) {});
    }

    void AppRSocketClient::disconnect()
    {
        if (_client) {
            _client->disconnect();
        }
        _open = false;
        _client = nullptr;
    }

    const std::unique_ptr<rsocket::RSocketClient> &AppRSocketClient::get_client() const
    {
        return _client;
    }

    const std::shared_ptr<rsocket::RSocketStats> &AppRSocketClient::get_stats() const
    {
        return _stats;
    }
    folly::EventBase *AppRSocketClient::get_connect_event_base() const
    {
        return _connect_event_base;
    }
    folly::EventBase *AppRSocketClient::get_app_client_event_base() const
    {
        return _app_client_event_base;
    }

    ConnectionEvents::ConnectionEvents(AppRSocketClient *app_rsocket_client)
    {
        this->_app_rsocket_client = app_rsocket_client;
        std::cout << "ConnectionEvents" << std::endl;
    }
    ConnectionEvents::~ConnectionEvents() {}

    void ConnectionEvents::onConnected()
    {
        std::cout << "onConnected" << std::endl;
        _app_rsocket_client->_open = true;
    }

    void ConnectionEvents::onDisconnected(const folly::exception_wrapper &)
    {
        std::cout << "onDisconnected" << std::endl;
    }
    void ConnectionEvents::onClosed(const folly::exception_wrapper &e)
    {
        std::cout << "onClosed" << std::endl;
        onDisconnected(e);
    }
    void ConnectionEvents::onStreamsPaused()
    {
        std::cout << "onStreamsPaused" << std::endl;
    }
    void ConnectionEvents::onStreamsResumed()
    {
        std::cout << "onStreamsResumed" << std::endl;
    }
} // namespace bdlbsc