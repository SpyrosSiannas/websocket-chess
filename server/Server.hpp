#ifndef SERVER_H
#define SERVER_H
#include <App.h>
#include <string>
#include <unordered_map>

namespace server {
struct UserData {
  unsigned int sessionId;
  unsigned int uuid;
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

private:
  enum class MessageType {
    CREATE_SESSION,
    JOIN_SESSION,
    CLOSE_SESSION,
  };
  std::vector<unsigned int> sessions;
  uWS::App _app{};
  unsigned int _port;
  unsigned int _last_uuid{0};
  const std::unordered_map<MessageType, std::string_view> msgHeads{
      {{MessageType::CREATE_SESSION, "create"},
       {MessageType::JOIN_SESSION, "join"},
       {MessageType::CLOSE_SESSION, "close"}}};
};
} // namespace server

#endif // SERVER_H
