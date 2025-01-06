#ifndef ROUTE_H
#define ROUTE_H

#include "HttpRequest.h"
#include "HttpMethods.h"
#include <string>

class Route
{
    private:
        std::string uri;
        HttpMethods method;

        std::function<std::string(HttpRequest& request)> handler;
    public:
        Route() = default;
        Route(const std::string& uri, const std::string& method, const std::function<std::string(HttpRequest& request)>& handler);
        std::string get_uri() const;
        HttpMethods get_method() const;
        ~Route();
};

#endif
