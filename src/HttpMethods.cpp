#include "HttpMethods.h"
#include <string>



HttpMethods extract_method(const char* method)
{
    if (strcmp(method, "GET") == 0)
    {
        return GET;
    }
    else if (strcmp(method, "POST") == 0)
    {
        return POST;
    }
    else if (strcmp(method, "PUT") == 0)
    {
        return PUT;
    }
    else if (strcmp(method, "HEAD") == 0)
    {
        return HEAD;
    }
    else if (strcmp(method, "PATCH") == 0)
    {
        return PATCH;
    }
    else if (strcmp(method, "DELETE") == 0)
    {
        return DELETE;
    }
    else if (strcmp(method, "CONNECT") == 0)
    {
        return CONNECT;
    }
    else if (strcmp(method, "OPTIONS") == 0)
    {
        return OPTIONS;
    }
    else if (strcmp(method, "TRACE") == 0)
    {
        return TRACE;
    }
    else
    {
        return GET;
    }
}

std::string get_method_string(HttpMethods method)
{
    switch (method)
    {
    case GET:
        return "GET";
    case POST:
        return "POST";
    case PUT:
        return "PUT";
    case HEAD:
        return "HEAD";
    case PATCH:
        return "PATCH";
    case DELETE:
        return "DELETE";
    case CONNECT:
        return "CONNECT";
    case OPTIONS:
        return "OPTIONS";
    case TRACE:
        return "TRACE";
    default:
        return "GET";
    }
}