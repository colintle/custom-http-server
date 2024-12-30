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
        std::unordered_map<std::string, std::string> request_line_fields;
        std::unordered_map<char*, char*> header_fields;
        std::unordered_map<char*, char*> body_fields;

    public:
        HttpRequest(char* request_string);
        std::unordered_map<std::string, std::string> get_request_line_fields();
        std::unordered_map<char*, char*> get_header_fields();
        std::unordered_map<char*, char*> get_body_fields();
        ~HttpRequest();
};

#endif