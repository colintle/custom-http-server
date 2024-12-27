#include "HTTPRequest.h"

#include <stdio.h>
#include <string>
#include <queue>

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

    return GET;
}

HttpRequest::HttpRequest(char* request_string)
{
    char requested[strlen(request_string)];
    strcpy(requested, request_string);

    for (unsigned long i = 0; i < strlen(requested) - 2; i++)
    {
        if (requested[i] == '\n' && requested[i + 1] == '\n')
        {
            requested[i+1] = '|';
            break;
        }
    }
    char* request_line = strtok(requested, "\n");
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

    this->header_fields = std::unordered_map<char*, char*>();
    std::queue<char*> header_fields_queue;
    char* token = strtok(header_fields, "\n");
    while (token != NULL)
    {
        header_fields_queue.push(token);
        token = strtok(NULL, "\n");
    }

    char* header = header_fields_queue.front();
    while (header != NULL)
    {
        char* key = strtok(header, ":");
        char* value = strtok(NULL, ":");
        this->header_fields[key] = value;
        header_fields_queue.pop();
        header = header_fields_queue.front();
    }
}