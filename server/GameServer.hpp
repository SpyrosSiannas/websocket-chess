#ifndef GAME_SERVER_H
#define GAME_SERVER_H

#include <App.h>
#include <string>
#include <string_view>
#include <unordered_map>

namespace server {
using std::string_view_literals::operator""sv;
using UID = unsigned int;

// To be replaced with a GameSession
struct DummySession {
  UID sessionId;
};

class GameServer final {
public:
  explicit GameServer(unsigned int port = 9001);
  ~GameServer() = default;
  void listen();

private:
  // TODO: Move from naive implementation to mt
  unsigned int generateUUID();
  void parseMessage(auto *ws, std::string_view message, uWS::OpCode opCode);
  void onJoin(auto *ws, std::string_view message, uWS::OpCode opCode);
  void onCreate(auto *ws, uWS::OpCode opCode);

private:
  std::unordered_map<UID, std::shared_ptr<DummySession>> _sessions;
  uWS::App _app{};
  unsigned int _port;
  UID _last_uuid{0};
  static constexpr auto MSG_CREATE_SESSION{R"(create)"sv};
  static constexpr auto MSG_JOIN_SESSION{R"(join)"sv};
  static constexpr auto MSG_CLOSE_SESSION{R"(close)"sv};
  struct UserData {
    std::shared_ptr<DummySession> sessionPtr{nullptr};
    UID uuid;
  };
};
} // namespace server

#endif // GAME_SERVER_H
