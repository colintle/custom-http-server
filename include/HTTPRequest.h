#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <unordered_map>
#include <string>
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
        std::unordered_map<std::string, std::string> header_fields;
        std::unordered_map<std::string, std::string> body_fields;

    public:
        HttpRequest(char* request_string);
        std::unordered_map<std::string, std::string> get_request_line_fields();
        std::unordered_map<std::string, std::string> get_header_fields();
        std::unordered_map<std::string, std::string> get_body_fields();
        ~HttpRequest();
};

#endif