#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>

class Server
{
	private:
		int domain;
		int service;
		int protocol;
		u_long interface;
		int port;
		int backlog;

		struct sockaddr_in address;

		int socket_fd;

	public:
		Server(int domain, int service, int protocol, u_long interface, int port, int backlog);

		int get_domain();
		int get_service();
		int get_protocol();
		u_long get_interface();
		struct sockaddr_in& get_address();
		int get_port();
		int get_backlog();
		int get_socket_fd();

		void start();
		void stop();
		~Server();
};

#endif
