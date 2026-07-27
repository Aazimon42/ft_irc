/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:08:39 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/08 17:20:40 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include "Channel.hpp"

Client::Client()
{}
Client::Client(int afd)
{
    this->fd = afd;
    this->nickname = "";
    this->username = "";
}

Client::~Client()
{}

int Client::getFd()
{
    return (this->fd);
}

void Client::join(std::string channelName, std::string key)
{
    Channel *channel = server->getChannel(channelName);
    if (channel->getPass() == key)
    {
        channel->addClient(this);
    }
}

std::string Client::getUsername(void)
{
	return (this->username);
}