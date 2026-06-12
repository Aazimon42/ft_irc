/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:31:13 by edi-maio          #+#    #+#             */
/*   Updated: 2026/06/12 22:23:46 by edi-maio         ###   ########.fr       */
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
        throw std::runtime_error("Error: Failed to create socket");
    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        throw std::runtime_error("Error: Failed to bind socket");
    if (listen(fd, 16) < 0)
		throw std::runtime_error("Error: Failed to listen on socket");
    if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
        throw std::runtime_error("Error: Failed to set non-blocking");
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
        for (int i = 0; i < pollfds.size(); i++)
        {
            char buf[4096];
            if (pollfds[i].revents)
                recv(pollfds[i].fd, buf, 4095, 0);
            
        }
    }
}
