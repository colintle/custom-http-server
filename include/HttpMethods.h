#ifndef HTTPMETHODS_H
#define HTTPMETHODS_H

#include <string>

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

std::string get_method_string(HttpMethods method);
HttpMethods extract_method(const char* method);

#endif
