/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:31:13 by edi-maio          #+#    #+#             */
/*   Updated: 2026/06/27 22:41:01 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

Server::Server(int port, std::string password)
{
    this->running = 0;
    this->port = port;
    this->password = password;
}

void Server::start()
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
        for (int i = 0; i < pollfds.size(); i++)
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
