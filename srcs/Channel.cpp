/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 16:11:39 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/31 01:04:45 by edi-maio         ###   ########.fr       */
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
    restricted_topic = false;
    topic = "";
    password = "";
}

Channel::~Channel()
{}

void Channel::broadcast(const std::string& message, Client* sender)
{
    for (std::vector<Client*>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        Client* client = *it;
        if (client != sender)
            send(client->getFd(), message.c_str(), message.length(), 0);
    }
}

void Channel::addClient(Client* client)
{
    if (!isInChannel(client))
        clients.push_back(client);
}

void Channel::removeClient(Client *client)
{
    if (isInChannel(client))
    {
        bool wasOperator = isOperator(client);

        clients.erase(std::remove(clients.begin(), clients.end(), client), clients.end());
        operators.erase(std::remove(operators.begin(), operators.end(), client), operators.end());

        // If an operator left and there are still clients but no operators, promote the first client
        if (wasOperator && operators.empty() && !clients.empty())
            operators.push_back(clients.front());
    }
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

void Channel::setTopic(std::string topic)
{
    this->topic = topic;
}

void Channel::setPass(std::string pass)
{
    this->password = pass;
}

void Channel::setMaxUsers(int max)
{
    this->max_users = max;
}

void Channel::setInviteOnly(bool invite_only)
{
    this->invite_only = invite_only;
}

void Channel::setRestrictedTopic(bool restricted_topic)
{
    this->restricted_topic = restricted_topic;
}

void Channel::addOperator(Client* client)
{
    if (!isOperator(client))
        operators.push_back(client);
}

void Channel::removeOperator(Client* client)
{
    operators.erase(std::remove(operators.begin(), operators.end(), client), operators.end());
}

int Channel::getMaxUsers()
{
    return max_users;
}

