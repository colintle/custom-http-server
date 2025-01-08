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
        using RouteHandler = std::function<std::string(HttpRequest& request)>;

        HttpServer(int domain, int service, int protocol, u_long interface, int port, int backlog);
        ~HttpServer();

        void registerRoutes(const std::string& uri, const std::string& method, RouteHandler handler);
        void handle_request(int clientSocket);
        void launch() override;
};

// std::string renderTemplate(const std::vector<std::string>& templates);

#endif
