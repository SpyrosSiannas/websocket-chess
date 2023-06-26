#include <iostream>
#include "App.h"
#include "WebSocketProtocol.h"

int main(){
    struct UserData {
    };
    unsigned int conn_count = 0;

    uWS::App app;
    app.ws<UserData>("/*", {
    .upgrade = nullptr,
    .open = [&conn_count](auto /*ws*/) {
        conn_count++;
        std::cout << "Conn open!" << std::endl;
    },
    .message = [](auto *ws, std::string_view msg, uWS::OpCode opCode) {
        std::cout << msg << std::endl;
        ws->send(msg, opCode);
    },
    .close = [&app, &conn_count](auto, int, std::string_view) {
        conn_count--;
        if (conn_count == 0){
          app.close();
        }
    },
    }).listen(9001, [](auto *listen_socket){
        if (listen_socket) {
            std::cout<< "Listening to port: " << 9001 << std::endl;
        }
    });
    app.run();
    
    std::cout << "App Closed" << std::endl;
}
