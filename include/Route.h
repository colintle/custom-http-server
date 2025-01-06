#ifndef ROUTE_H
#define ROUTE_H

#include <HttpServer.h>
#include <HttpRequest.h>
#include <Route.h>
#include <string>

class Route
{
    private:
        std::string uri;
        HttpMethods method;
        std::function<std::string(HttpServer&, HttpRequest&)> handler;
    public:
        Route(const std::string& uri, const std::string& method, const std::function<std::string(HttpServer&, HttpRequest&)>& handler);
        std::string get_uri() const;
        HttpMethods get_method() const;
        ~Route();
};

#endif