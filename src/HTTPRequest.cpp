#include "HttpRequest.h"

#include <iostream>

std::unordered_map<std::string, std::string> parse_header_fields(char* header_fields)
{
    std::unordered_map<std::string, std::string> headers;

    char* token = strtok(header_fields, "\n");
    while (token != NULL)
    {
        char* colon_pos = strchr(token, ':');
        if (colon_pos != NULL)
        {
            std::string key(token, colon_pos - token);
            std::string value(colon_pos + 1);

            size_t start = value.find_first_not_of(" ");
            size_t end = value.find_last_not_of(" ");
            value = value.substr(start, end - start + 1);

            headers[key] = value;
        }
        token = strtok(NULL, "\n");
    }
    return headers;
}

std::unordered_map<std::string, std::string> parse_request_line_fields(char* request_line_fields)
{
    std::unordered_map<std::string, std::string> request_line = std::unordered_map<std::string, std::string>();
    char* method = strtok(request_line_fields, " ");
    request_line["method"] = std::string(method);

    char* uri = strtok(NULL, " ");
    request_line["uri"] = std::string(uri);

    char* version = strtok(NULL, " ");
    version = strtok(version, "/");
    version = strtok(NULL, "/");
 
    request_line["version"] = std::string(version);

    return request_line;
}

std::unordered_map<std::string, std::string> parse_body_fields(char* body_fields, std::string content_type)
{
    std::unordered_map<std::string, std::string> body = std::unordered_map<std::string, std::string>();
    if (!content_type.empty())
    {        
        if ((content_type.compare("application/x-www-form-urlencoded")) == 0)
        {
            char* token = strtok(body_fields, "&");
            while (token != NULL)
            {
                char* key = strtok(token, "=");
                char* value = strtok(NULL, "=");
                body[std::string(key)] = std::string(value);
                token = strtok(NULL, "&");
            }
        }
        else if ((content_type.compare("application/json")) == 0)
        {
            char* token = strtok(body_fields, ",");
            while (token != NULL)
            {
                char* key = strtok(token, ":");
                char* value = strtok(NULL, ":");
                body[std::string(key)] = std::string(value);
                token = strtok(NULL, ",");
            }
        }
        else
        {
            body["body"] = std::string(body_fields);
        }
    }
    return body;
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
        }
    }
    char* request_line = strtok(requested, "\n"); 
    char* header_fields = strtok(NULL, "|");
    char* body = strtok(NULL, "|");

    this->request_line_fields = parse_request_line_fields(request_line);
    this->header_fields = parse_header_fields(header_fields);

    if (this->request_line_fields["method"] == "POST")
    {
        this->body_fields = parse_body_fields(body, this->header_fields["Content-Type"]);
    }
}

std::unordered_map<std::string, std::string> HttpRequest::get_request_line_fields()
{
    return this->request_line_fields;
}

std::unordered_map<std::string, std::string> HttpRequest::get_header_fields()
{
    return this->header_fields;
}

std::unordered_map<std::string, std::string> HttpRequest::get_body_fields()
{
    return this->body_fields;
}

HttpRequest::~HttpRequest()
{
    this->request_line_fields.clear();
    this->body_fields.clear();
    this->header_fields.clear();
}
