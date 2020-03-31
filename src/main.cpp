#include <iostream>

#include <folly/init/Init.h>
#include <folly/io/async/ScopedEventBaseThread.h>
#include <folly/portability/GFlags.h>

#include "rsocket/RSocket.h"
#include "rsocket/examples/util/ExampleSubscriber.h"
#include "rsocket/transports/tcp/TcpConnectionFactory.h"

#include "yarpl/Flowable.h"
#include "yarpl/Single.h"

#include "MetaDataRouteUtils.h"

#include "MetaDataRouteUtils.h"

DEFINE_string(host, "192.168.0.43", "host to connect to");
DEFINE_int32(port, 7000, "host:port to connect to");

using namespace bdlbsc;
//
//int main1(int argc, char *argv[])
//{
//    FLAGS_logtostderr = true;
//    FLAGS_minloglevel = 0;
//    folly::init(&argc, &argv);
//
//    folly::SocketAddress address;
//    address.setFromHostPort(FLAGS_host, FLAGS_port);
//
//    folly::ScopedEventBaseThread worker;
//
//    auto client = rsocket::RSocket::createConnectedClient(
//                      std::make_unique<rsocket::TcpConnectionFactory>(*worker.getEventBase(), std::move(address)),
//                      rsocket::SetupParameters("message/x.rsocket.routing.v0", "application/json"),
//                      nullptr,
//                      std::chrono::seconds(60 * 60),
//                      nullptr,
//
//                      std::make_shared<ConnectionEvents>()
//
//                          )
//                      .get();
//
//    std::string data = "{\"origin\":\"Client\",\"interaction\":\"Request\"}";
//
//    char *metadata = MetaDataRouteUtils::string_to_char_p("hello");
//
//    client->getRequester()->requestResponse(rsocket::Payload(data.data(), metadata))->subscribe([](rsocket::Payload p) {
//        std::cout << "requestResponse Received :  >> " << p.moveDataToString() << std::endl;
//    });
//
//    client->getRequester()->fireAndForget(rsocket::Payload(data.data(), MetaDataRouteUtils::string_to_char_p("fire-and-forget")))->subscribe([]() {
//        std::cout << "fire-and-forget" << std::endl;
//    });
//
//    client->getRequester()->fireAndForget(rsocket::Payload(data.data(), MetaDataRouteUtils::string_to_char_p("fire-and-forget")))->subscribe([]() {
//        std::cout << "fire-and-forget" << std::endl;
//    });
//
//    client->getRequester()->requestStream(rsocket::Payload(data.data(), MetaDataRouteUtils::string_to_char_p("stream")))->subscribe([](rsocket::Payload p) {
//        std::cout << " requestStream Received : " << p.moveDataToString() << std::endl;
//    });
//
//    client->getRequester()
//        ->requestChannel(
//            rsocket::Payload(data.data(), MetaDataRouteUtils::string_to_char_p("channel")),
//            yarpl::flowable::Flowable<>::justN({ data.data(), data.data(), data.data(), data.data(), data.data(), data.data() })->map([](char *v) {
//                return rsocket::Payload(v, MetaDataRouteUtils::string_to_char_p("channel"));
//            }))
//        ->subscribe([](rsocket::Payload p) { std::cout << "channel Received : " << p.moveDataToString() << std::endl; });
//
//    std::getchar();
//
//    return 0;
//}

#include "AppRSocketClient.h"
int main(int argc, char *argv[])
{

    FLAGS_logtostderr = true;
    FLAGS_minloglevel = 0;
    folly::init(&argc, &argv);

    AppRSocketClient *_app_rsocket_client = new AppRSocketClient("192.168.0.43", 7000);

    if (_app_rsocket_client->_open) {

        _app_rsocket_client->get_app_client_event_base()->getEventBase()->add([_app_rsocket_client]() {
            std::string data = "{\"origin\":\"Client\",\"interaction\":\"Request\"}";

            char *metadata = MetaDataRouteUtils::string_to_char_p("hello");

            _app_rsocket_client->get_client()
                ->getRequester()
                ->requestResponse(rsocket::Payload(data.data(), metadata))
                ->subscribe([_app_rsocket_client](rsocket::Payload p) {
                    std::cout << "requestResponse Received :  >> " << p.moveDataToString() << std::endl;
                    _app_rsocket_client->disconnect();
                });
        });
    }

    std::getchar();
}