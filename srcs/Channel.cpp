/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 16:11:39 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/28 01:21:56 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <algorithm>

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
    (void)sender;
    for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        Client* client = *it;
        send(client->getFd(), message.c_str(), message.length(), 0);
    }
}

void Channel::addClient(Client* client)
{
    if (!isInChannel(client))
        clients.push_back(client);
}

void Channel::addInvited(Client* client)
{
    invited.push_back(client);
}

std::string Channel::getPass()
{
    return password;
}

std::string Channel::getName()
{
    return name;
}

std::string Channel::getTopic()
{
    return topic;
}

std::string Channel::getUsers()
{
    std::string users;
    for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        Client* client = *it;
        if (isOperator(client))
            users += "@";
        users += client->getUsername();
        if (it + 1 != clients.end())
            users += " ";
    }
    return users;
}

bool Channel::isInviteOnly()
{
    return invite_only;
}

bool Channel::isRestrictedTopic()
{
    return restricted_topic;
}

bool Channel::isOperator(Client* client)
{
    return std::find(operators.begin(), operators.end(), client) != operators.end();
}

bool Channel::isInChannel(Client* client)
{
    return std::find(clients.begin(), clients.end(), client) != clients.end();
}