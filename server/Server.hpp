#ifndef SERVER_H
#define SERVER_H
#include <App.h>
#include <string>
#include <string_view>
#include <unordered_map>

namespace server {
// using only specific operator
using std::string_view_literals::operator""sv;
using UID = unsigned int;

// To be replaced with a GameSession
struct DummySession {
  UID sessionId;
};

struct UserData {
  std::shared_ptr<DummySession> sessionPtr{nullptr};
  UID uuid;
};

class Server final {
public:
  explicit Server(unsigned int port = 9001);
  ~Server() = default;
  void listen();

private:
  // TODO: Move from naive implementation to mt
  unsigned int generateUUID();
  void parseMessage(auto *ws, std::string_view message, uWS::OpCode opCode);
  void onJoin(auto *ws, std::string_view message);
  void onCreate(auto *ws);

private:
  std::unordered_map<UID, std::shared_ptr<DummySession>> sessions;
  uWS::App _app{};
  unsigned int _port;
  UID _last_uuid{0};
  static constexpr auto MSG_CREATE_SESSION{R"(create)"sv};
  static constexpr auto MSG_JOIN_SESSION{R"(join)"sv};
  static constexpr auto MSG_CLOSE_SESSION{R"(close)"sv};
};
} // namespace server

#endif // SERVER_H
