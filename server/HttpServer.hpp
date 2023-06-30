#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H
#include <App.h>
#include <utils/AsyncFileStreamer.hpp>

namespace server {
class HttpServer final {
public:
  HttpServer();
  ~HttpServer() = default;
  void listen();

private:
  uWS::App _app{};
  std::unique_ptr<utils::AsyncFileStreamer> streamer{std::make_unique<utils::AsyncFileStreamer>("www")};
  static constexpr unsigned int HTTP_PORT{80};
  struct UserData {};
};
} // namespace server
#endif // HTTP_SERVER_H
