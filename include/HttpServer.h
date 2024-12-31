#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include "server.h"
#include "HttpRequest.h"

class HttpServer: public Server
{
    public:
        using RouteHandler = std::function<std::string(HttpServer&, HttpRequest&)>;

        HttpServer();
        ~HttpServer();

        void registerRoutes(const std::string& uri, RouteHandler handler, const std::vector<std::string>& methods);
        void launch();
        static std::string renderTemplate(const std::vector<std::string>& templates);
};

#endif