#include "server/Server.hpp"
#include <iostream>

int main() {
  server::Server srv{9001};
  srv.listen();
  std::cout << "App Closed" << std::endl;
}
