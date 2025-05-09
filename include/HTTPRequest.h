#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include "HttpMethods.h"

#include <unordered_map>
#include <variant>
#include <string>
#include <stdio.h>

class HttpRequest
{
    private:
        std::unordered_map<std::string, std::variant<HttpMethods, std::string>> request_line_fields;
        std::unordered_map<std::string, std::string> header_fields;
        std::unordered_map<std::string, std::string> body_fields;

    public:
        HttpRequest(char* request_string);
        std::unordered_map<std::string, std::variant<HttpMethods, std::string>> get_request_line_fields();
        std::unordered_map<std::string, std::string> get_header_fields();
        std::unordered_map<std::string, std::string> get_body_fields();
        std::string get_uri();
        ~HttpRequest();
};

#endif
