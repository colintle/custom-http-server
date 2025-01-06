#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <unordered_map>
#include "server.h"
#include "Route.h"

class HttpServer: public Server
{
    protected:
        std::unordered_map<std::string, Route> routes;
    public:
        using RouteHandler = std::function<std::string(HttpServer&, HttpRequest&)>;

        HttpServer(int domain, int service, int protocol, u_long interface, int port, int backlog);
        ~HttpServer();

        void registerRoutes(const std::string& uri, RouteHandler handler, const std::vector<std::string>& methods);
        void launch() override;
};

// std::string renderTemplate(const std::vector<std::string>& templates);

#endif
