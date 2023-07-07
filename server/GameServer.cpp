#include <iostream>
#include <server/GameServer.hpp>

namespace server {
GameServer::GameServer(unsigned int port) {
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

void GameServer::parseMessage(auto *ws, std::string_view message,
                              uWS::OpCode opCode) {
  if (message.starts_with(MSG_CREATE_SESSION)) {
    onCreate(ws, opCode);
  } else if (message.starts_with(MSG_JOIN_SESSION)) {
    onJoin(ws, message, opCode);
  }
}

void GameServer::onJoin(auto *ws, std::string_view message,
                        uWS::OpCode opCode) {
  UID sessID;
  const size_t delimPos{message.find_first_of(' ')};
  std::from_chars(message.data() + delimPos + 1,
                  message.data() + message.size(), sessID);
  if (auto it = _sessions.find(sessID); it != _sessions.end()) {
    // auto team = Session->registerPlayer() (std::optional?)
    auto msg = "Joined Session " + std::to_string(sessID);
    ws->send(msg, opCode);
  }
}

void GameServer::onCreate(auto *ws, uWS::OpCode opCode) {
  std::cout << "Creating session" << std::endl;
  auto sess{ws->getUserData()->sessionPtr};
  const auto sessionId = generateUUID();
  auto session{std::make_shared<DummySession>()};
  session->sessionId = sessionId;
  // id is unique
  _sessions.insert(std::make_pair(sessionId, session));
  ws->getUserData()->sessionPtr = session;
  ws->send(std::to_string(sessionId), opCode);
}

void GameServer::listen() {
  _app.listen(_port, [this](auto *listen_socket) {
    if (listen_socket) {
      std::cout << "Listening on port: " << _port << std::endl;
    }
  });
}

unsigned int GameServer::generateUUID() { return ++_last_uuid; }
} // namespace server
