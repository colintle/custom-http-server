#include "HttpServer.h"
#include "HttpRequest.h"
#include "Route.h"
#include "ThreadPool.h"
#include <iostream>
#include <unistd.h>

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

        ssize_t bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);
        if (bytesRead < 0) {
            std::cerr << "Failed to read from client socket" << std::endl;
            close(clientSocket);
            return;
        }

        HttpRequest request(buffer);

        const char* response = 
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/plain\n"
            "Content-Length: 12\n\n"
            "Hello world!";
		
        write(clientSocket, response, strlen(response));
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
