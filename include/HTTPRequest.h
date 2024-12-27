#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <stdio.h>

enum HttpMethods
{
    GET,
    POST,
    PUT,
    HEAD,
    PATCH,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE
};

class HttpRequest
{
    private:
        HttpMethods method;
        char* uri;
        float version;

    public:
        HttpRequest(char* request_string);
        HttpMethods get_method();
        char* get_uri();
        float get_version();
        ~HttpRequest();
};

#endif HTTPREQUEST_H