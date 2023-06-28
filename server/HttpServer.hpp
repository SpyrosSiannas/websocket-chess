#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H
#include <App.h>

namespace server {
class HttpServer final {
public:
  HttpServer();
  ~HttpServer() = default;
  void listen();

private:
  uWS::App _app{};
  static constexpr unsigned int HTTP_PORT{80};
  struct UserData {};
};
} // namespace server
#endif // HTTP_SERVER_H
