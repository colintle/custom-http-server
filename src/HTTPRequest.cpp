#include "HTTPRequest.h"

#include <stdio.h>
#include <string>

HttpMethods method_select(char* method)
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
}

HttpRequest::HttpRequest(char* request_string)
{
    for (int i = 0; i < strlen(request_string) - 1; i++)
    {
        if (request_string[i] == '\n' && request_string[i + 1] == '\n')
        {
            request_string[i+1] = '| ';
            break;
        }
    }
    char* request_line = strtok(request_string, "\n");
    char* header_fields = strtok(NULL, "|");
    char* body = strtok(NULL, "|");

    char* method = strtok(request_line, " ");
    this->method = method_select(method);

    char* uri = strtok(NULL, " ");
    this->uri = uri;

    char* version = strtok(NULL, " ");
    version = strtok(version, "/");
    version = strtok(NULL, "/");

    this->version = atof(version);

    return;
}