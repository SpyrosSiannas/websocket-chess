#include <HttpServer.hpp>

namespace server {

HttpServer::HttpServer() {
  _app.get("/*", [](auto *res, auto /**req*/) {
    res->writeHeader("Content-Type", "text")->end("Yooo");
  });
  _app.ws<UserData>("/*", {});
}

void HttpServer::listen() {
  _app.listen(HTTP_PORT, [](auto *listen_socket) {
    if (listen_socket) {
      std::cout << "Listening on port 80" << std::endl;
    } else {
      std::cout << "Failed to listen at port 80" << std::endl;
    }
  });
}

} // namespace server
