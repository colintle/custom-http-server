#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include "Server.h"
#include "Route.h"
#include <unordered_map>

class HttpServer: public Server
{
    protected:
        std::unordered_map<std::string, Route> routes;
    public:
        HttpServer(int domain, int service, int protocol, u_long interface, int port, int backlog);
        ~HttpServer();

        void register_route(const std::string& uri, const std::string& method, const std::string& file_path);
        void handle_request(int clientSocket);
        void launch() override;
};

#endif
