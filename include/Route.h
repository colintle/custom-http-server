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
        std::string file_path;
    public:
        Route() = default;
        Route(const std::string& uri, const std::string& method, const std::string& file_path);
        std::string get_uri() const;
        HttpMethods get_method() const;
        std::string get_file_path() const;
        ~Route();
};

#endif
