#include "HttpServer.h"
#include "HttpRequest.h"
#include "Route.h"
#include "ThreadPool.h"
#include <iostream>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

char* render_template(const char* template_path)
{
    FILE* file = fopen(template_path, "r");
    if (!file)
    {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    if (file_size <= 0) {
        fclose(file);
        return strdup("");
    }

    char* buffer = (char*)malloc(file_size + 1);
    if (!buffer)
    {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    if (bytes_read != (size_t)file_size) {
        perror("Failed to read the complete file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[bytes_read] = '\0';
    fclose(file);

    return buffer;
}

HttpServer::HttpServer(int domain, int service, int protocol, u_long interface, int port, int backlog)
    : Server(domain, service, protocol, interface, port, backlog)
{
    return;
}

void HttpServer::launch() {
    ThreadPool threadPool(5);
    struct sockaddr_in* address = &this->address;

    while (true) {
        int addrSize = sizeof(this->address);
        int clientSocket = accept(this->socket_fd, (struct sockaddr*)address, (socklen_t*)&addrSize);

        if (clientSocket < 0) {
            std::cerr << "Failed to accept connection" << std::endl;
            continue;
        }

        threadPool.enqueue([clientSocket, this]() {
            handle_request(clientSocket);
        });
    }
}

void HttpServer::handle_request(int clientSocket) {
    try {
        char buffer[60000] = {0};

        std::cout << "Handling request" << std::endl;

        ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);
        if (bytesRead < 0) {
            std::cerr << "Failed to read from client socket" << std::endl;
            close(clientSocket);
            return;
        }

        HttpRequest request = HttpRequest(buffer);

        std::string filePath = this->routes[request.get_uri()].get_file_path();
        char* response = render_template(filePath.c_str());


        if (!response) {
            const char* errorResponse = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n";
            write(clientSocket, errorResponse, strlen(errorResponse));
        } else {
            std::string httpResponse = "HTTP/1.1 200 OK\r\n";
            httpResponse += "Content-Length: " + std::to_string(strlen(response)) + "\r\n\r\n";
            httpResponse += response;

            write(clientSocket, httpResponse.c_str(), httpResponse.size());
            free(response);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error handling client request: " << e.what() << std::endl;
    }
    close(clientSocket);
}

void HttpServer::register_route(const std::string& uri, const std::string& method, const std::string& file_path)
{
	Route route = Route(uri, method, file_path);
	this->routes[uri] = route;
	return;
}

HttpServer::~HttpServer()
{
    return;
}
