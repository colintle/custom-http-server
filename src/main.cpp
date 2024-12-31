#include <iostream>
#include <unistd.h>
#include "HttpServer.h"

int main()
{
	HttpServer server(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 5);
	server.start();
	server.launch();
	return 0;
}
