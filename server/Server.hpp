#ifndef SERVER_H
#define SERVER_H
#include <GameServer.hpp>
#include <HttpServer.hpp>
#include <Loop.h>

namespace server {

// Runs the event loop
static inline void run() { uWS::run(); };

} // namespace server

#endif // SERVER_H
