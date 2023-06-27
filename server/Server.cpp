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
                          uWS::OpCode /*opCode*/) {
  if (message.starts_with(MSG_CREATE_SESSION)) {
    onCreate(ws);
  } else if (message.starts_with(MSG_JOIN_SESSION)) {
    onJoin(ws, message);
  }
}

void Server::onJoin(auto *ws, std::string_view message) {
  auto sess{ws->getUserData()->sessionPtr};
  UID sessID;
  const size_t delimPos{message.find_first_of(' ')};
  std::from_chars(message.data() + delimPos + 1,
                  message.data() + message.size(), sessID);
  if (auto it = sessions.find(sessID); it != sessions.end()) {
    // auto team = Session->registerPlayer() (std::optional?)
    auto msg = "Joined Session" + std::to_string(sessID);
    ws->send(msg);
  }
}

void Server::onCreate(auto *ws) {
  const auto sessionId = generateUUID();
  auto session{std::make_shared<DummySession>()};
  session->sessionId = sessionId;
  // id is unique
  sessions.insert(std::make_pair(sessionId, session));
  ws->getUserData()->sessionPtr = session;
  ws->send(std::to_string(sessionId));
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
