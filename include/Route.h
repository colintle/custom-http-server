#ifndef ROUTE_H
#define ROUTE_H

#include <string>
#include "HttpServer.h"
#include "HttpRequest.h"

class Route
{
    private:
        std::string uri;
        int methods[9];
        std::function<std::string(HttpServer&, HttpRequest&)> handler;
    public:
        Route(const std::string& uri, const std::string& method, const std::string& response);
        std::string get_uri() const;
        int get_method() const;
        ~Route();
};

#endif