/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:31:13 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/08 17:08:14 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, std::string password)
{
    this->running = 0;
    this->port = port;
    this->password = password;
}
Server::~Server()
{}
void Server::init()
{
    this->running = 1;
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
        throw IrcException("Error: Failed to create socket");
    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        throw IrcException("Error: Failed to bind socket");
    if (listen(fd, 16) < 0)
		throw IrcException("Error: Failed to listen on socket");
    if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
        throw IrcException("Error: Failed to set non-blocking");
    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    this->pollfds.push_back(pfd);
}

void Server::run()
{
    while (running)
    {
        if (poll(&pollfds[0], pollfds.size(), -1) < 0)
		{
            throw IrcException("Error: Failed to Poll");
		}
        for (unsigned long i = 0; i < pollfds.size(); i++)
        {
            if (pollfds[i].revents & POLLIN)
            {
                if (pollfds[i].fd == this->fd)
                    acceptClient();
                else
                    handleClientData(i);
            }
            if (pollfds[i].revents & (POLLHUP | POLLERR))
                disconnectClient(i);
        }
    }
}

void Server::acceptClient()
{
    int client_fd = accept(this->fd, NULL, NULL);
    if (client_fd < 0)  
        return ;
    fcntl(client_fd, F_SETFL, O_NONBLOCK);
    Client *client = new Client(client_fd);
    this->clients.push_back(client);
        struct pollfd pfd;
    pfd.fd = client_fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    this->pollfds.push_back(pfd);
    std::cout << "nouveau client"<< std::endl;
}

void Server::handleClientData(int i)
{
    char buffer[512];
    std::memset(buffer, 0, sizeof(buffer));

    int n = recv(pollfds[i].fd, buffer, sizeof(buffer) - 1, 0);

    if (n <= 0)
    {
        disconnectClient(i);
        return ;
    }
    buffer[n] = '\0';
    handle_input(i, buffer);
    std::cout << "Received from fd " << pollfds[i].fd << ": " << buffer;
}

Command *Server::handle_input(int i, char *buffer)
{
    std::string commands[12] = {"JOIN"};
    int command = 0;
    Client *client = getClientFromFd(pollfds[i].fd);
    std::vector<std::string> args = split(buffer, ' ');
    while (command < 12)
    {
        if (commands[command] == buffer)
            break;
        command++;
    }
    switch (command)
    {
        case (0):
            return new JoinCommand(this, client, args);
        default:
            std::cout << "Unknown command: " << command << std::endl;
            return (NULL);
    }
}

Client *Server::getClientFromFd(int fd)
{
    for (size_t i = 0; i < clients.size(); i++)
    {
        if (clients[i]->getFd() == fd)
            return clients[i];
    }
    return NULL;
}

Channel *Server::getChannel(std::string name)
{
    for (size_t i = 0; i < channels.size(); i++)
    {
        if (channels[i]->getName() == name)
            return channels[i];
    }
    return NULL;
}

void Server::disconnectClient(int i)
{
    int client_fd = pollfds[i].fd;
    close(client_fd);

    for (size_t j = 0; j < clients.size(); j++)
    {
        if (clients[j]->getFd() == client_fd)
        {
            delete clients[j];
            clients.erase(clients.begin() + j);
            break;
        }
    }
    pollfds.erase(pollfds.begin() + i);
}