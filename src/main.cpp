#include "HttpServer.h"
#include <iostream>
#include <unistd.h>

int main()
{
	HttpServer server(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 5);
	server.register_route("/", "GET", "frontend/hello.html");
	server.start();
	server.launch();
	return 0;
}
