#include "Server.h"
#include <stdio.h>

Server::Server(int domain, int service, int protocol, u_long interface, int port, int backlog)
{
	this->domain = domain;
	this->service = service;
	this->protocol = protocol;
	this->interface = interface;
	this->port = port;
	this->backlog = backlog;
	
	this->address.sin_family = domain;
	this->address.sin_port = htons(port);
	this->address.sin_addr.s_addr = htonl(interface);

}

void Server::start(){
	
	this->socket_fd = socket(this->domain, this->service, this->protocol);

	if (this->socket_fd < 0)
	{
		perror("Failed to connect socket... \n");
		exit(1);
	}

	if (bind(this->socket_fd, (struct sockaddr *)&this->address, sizeof(this->address)) < 0){
		perror("Failed to bind socket... \n");
		exit(1);
	}

	if (listen(this->socket_fd, this->backlog) < 0){
		perror("Failed to listen on socket... \n");
		exit(1);
	}
}

int Server::get_domain() const {
	return this->domain;
}

int Server::get_service() const {
	return this->service;
}

int Server::get_protocol() const {
	return this->protocol;
}

u_long Server::get_interface() const {
	return this->interface;
}

const struct sockaddr_in& Server::get_address() const {
	return this->address;
}

int Server::get_port() const {
	return this->port;
}

int Server::get_backlog() const {
	return this->backlog;
}

int Server::get_socket_fd() const {
	return this->socket_fd;
}

void Server::launch(){
}

Server::~Server(){
}
