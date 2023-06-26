#include <iostream>
#include <server/Server.hpp>
#include <string>

template <typename T> void ignore_unused(T &) {}

namespace server {
Server::Server(unsigned int port) {
  _port = port;
  _app.ws<UserData>(
      "/*", {
                .upgrade = nullptr,
                .open = [](auto /*ws*/) {},
                .message =
                    [this](auto *ws, std::string_view msg, uWS::OpCode opCode) {
                      // this->parseMessage(ws, msg, opCode);
                      parseMessage(ws, msg, opCode);
                    },
                .close = [](auto /*ws*/, int, std::string_view /*msg*/) {},
            });
}

void Server::parseMessage(auto *ws, std::string_view message,
                          uWS::OpCode opCode) {
  if (message.starts_with(msgHeads.at(MessageType::CREATE_SESSION))) {
    auto sessionID = generateUUID();
    sessions.push_back(sessionID);
    ws->getUserData()->sessionId = sessionID;
    ws->send(std::to_string(sessionID), opCode);
  } else if (message.starts_with(msgHeads.at(MessageType::JOIN_SESSION))) {
    auto sessID = ws->getUserData()->sessionId;
    for (auto &id : sessions) {
      if (id == sessID) {
        ws->send("Joining Session", opCode);
      }
    }
  }
}

void Server::listen() {
  _app.listen(_port, [this](auto *listen_socket) {
    if (listen_socket) {
      std::cout << "Listening on port: " << _port << std::endl;
    }
  });

  _app.run();
}

unsigned int Server::generateUUID() { return ++_last_uuid; }
} // namespace server
