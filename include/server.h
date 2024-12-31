#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>

class Server
{
	protected:
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

		int get_domain() const;
		int get_service() const;
		int get_protocol() const;
		u_long get_interface() const;
		const struct sockaddr_in& get_address() const;
		int get_port() const;
		int get_backlog() const;
		int get_socket_fd() const;

		void start();

		virtual void launch();
		~Server();
};

#endif
