/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:31:13 by edi-maio          #+#    #+#             */
/*   Updated: 2026/06/12 17:59:43 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

Server::Server(int port, std::string password)
{
    this->running = 0;
    this->port = port;
    this->password = password;
}

void Server::start(int port, std::string password)
{
    this->running = 1;
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        std::cerr << "Error: Failed to create socket" << std::endl;
        exit(1);
    }
}

void Server::run()
{
    while (running)
    {
        break;
    }
}