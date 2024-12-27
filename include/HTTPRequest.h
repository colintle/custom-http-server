#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <unordered_map>
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
        std::unordered_map<char*, char*> header_fields;

    public:
        HttpRequest(char* request_string);
        HttpMethods get_method();
        char* get_uri();
        float get_version();
        ~HttpRequest();
};

#endif