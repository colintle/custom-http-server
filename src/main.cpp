#include <iostream>
#include <unistd.h>
#include <server.h>


void launch_server(Server& server){
	while (true){
		char buffer[30000];

		std::cout << "Waiting for Connection" << std::endl;

		int addr_size = sizeof(server.get_address());
		int new_socket = accept(server.get_socket_fd(), (struct sockaddr *)&server.get_address(), (socklen_t*)&addr_size);
		read(new_socket, buffer, 30000);

		std::cout << "Data: " << buffer << std::endl;

		const char* hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
		write(new_socket, hello, strlen(hello));
		close(new_socket);
	}
}

int main()
{
	std::cout << "Hello, World" << std::endl;
	Server server(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 5);
	server.start();
	launch_server(server);
	return 0;
}


