#include <server/Server.hpp>

int main(void) {
  server::GameServer srv{9001};
  server::HttpServer web{};
  srv.listen();
  web.listen();
  server::run();
}
