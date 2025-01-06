#include <HttpServer.h>
#include <iostream>
#include <unistd.h>
#include "HttpRequest.h"

HttpServer::HttpServer(int domain, int service, int protocol, u_long interface, int port, int backlog)
    : Server(domain, service, protocol, interface, port, backlog)
{
    return;
}

void HttpServer::launch()
{
    while (true){
		char buffer[60000];

		std::cout << "Waiting for Connection" << std::endl;

		int addr_size = sizeof(this->address);
		int new_socket = accept(this->socket_fd, (struct sockaddr *)&this->address, (socklen_t*)&addr_size);
		read(new_socket, buffer, 60000);

		HttpRequest request = HttpRequest(buffer);

		std::cout << "Request Line: " << std::endl;
		auto request_line_fields = request.get_request_line_fields();
		std::cout << get_method_string(std::get<HttpMethods>(request_line_fields["method"])) << " " << std::get<std::string>(request_line_fields["uri"]) << " " << std::get<std::string>(request_line_fields["version"]) << std::endl;

		const char* hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
		write(new_socket, hello, strlen(hello));
		close(new_socket);
	}
}

void HttpServer::registerRoutes(const std::string& uri, RouteHandler handler, const std::vector<std::string>& methods)
{
	return;
}

HttpServer::~HttpServer()
{
    return;
}

