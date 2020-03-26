#include <iostream>

#include <folly/init/Init.h>
#include <folly/io/async/ScopedEventBaseThread.h>
#include <folly/portability/GFlags.h>

#include "rsocket/RSocket.h"
#include "rsocket/examples/util/ExampleSubscriber.h"
#include "rsocket/transports/tcp/TcpConnectionFactory.h"

#include "yarpl/Single.h"

#include "StringUtils.h"

#include "ConnectionEvents.h"

DEFINE_string(host, "192.168.0.43", "host to connect to");
DEFINE_int32(port, 7000, "host:port to connect to");

int main(int argc, char *argv[]) {
  FLAGS_logtostderr = true;
  FLAGS_minloglevel = 0;
  folly::init(&argc, &argv);

  folly::SocketAddress address;
  address.setFromHostPort(FLAGS_host, FLAGS_port);

  folly::ScopedEventBaseThread worker;

  auto client = rsocket::RSocket::createConnectedClient(
                    std::make_unique<rsocket::TcpConnectionFactory>(
                        *worker.getEventBase(), std::move(address)),
                    rsocket::SetupParameters("message/x.rsocket.routing.v0",
                                             "application/json"),
                    nullptr, std::chrono::seconds(10), nullptr,

                    std::make_shared<ConnectionEvents>()

                        )
                    .get();

  std::string data = "{\"origin\":\"Client\",\"interaction\":\"Request\"}";

  char *metadata = StringUtils::string_to_char_p("hello");

  client->getRequester()
      ->requestResponse(rsocket::Payload(data.data(), metadata))
      ->subscribe([](rsocket::Payload p) {
        std::cout << "接收的数据 >> " << p.moveDataToString() << std::endl;
      });

  std::getchar();
  return 0;
}