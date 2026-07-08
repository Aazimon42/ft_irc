/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 16:11:39 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/08 17:14:53 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string name, Client* creator)
{
    this->name = name;
    clients.push_back(creator);
    operators.push_back(creator);
    max_users = 0;
    invite_only = false;
    topic = "";
    password = "";
}

void Channel::broadcast(const std::string& message, Client* sender)
{
    for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        Client* client = *it;
        if (client->getFd() != sender->getFd())
        {
            send(client->getFd(), message.c_str(), message.length(), 0);
        }
    }
}

void Channel::addClient(Client* client)
{
    clients.push_back(client);
}

std::string Channel::getPass()
{
    return password;
}

std::string Channel::getName()
{
    return name;
}