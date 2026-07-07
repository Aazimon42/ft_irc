/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 16:11:39 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/06 17:17:03 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"

Channel::Channel(std::string name, Client* creator)
{
    name = name;
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