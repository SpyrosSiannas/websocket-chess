#include <HttpServer.hpp>

namespace server {

HttpServer::HttpServer() {
  _app.get("/*", [this](auto *res, auto *req) {
    res->writeStatus(uWS::HTTP_200_OK);
    streamer->streamFile(res, req->getUrl());
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
