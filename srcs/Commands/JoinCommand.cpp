/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:11:40 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/28 01:18:19 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/JoinCommand.hpp"
#include "Server.hpp"

JoinCommand::JoinCommand(Server *server, Client *client, std::vector<std::string> args) : Command(server, client, args)
{}

JoinCommand::~JoinCommand()
{}

void JoinCommand::execute()
{
    std::cout << "Executing JOIN command for client: " << client->getUsername() << std::endl;
    if (args.size() == 1)
    {
        server->sendError(client->getFd(), 461, client->getUsername(), "JOIN");
        return;
    }

    std::vector<std::string> channels = split(args[1], ',');
    std::vector<std::string> keys;

    if (args.size() > 2)
        keys = split(args[2], ',');

    for (size_t i = 0; i < channels.size(); ++i)
    {
        std::string channelName = channels[i];
        std::string key;
        if (i < keys.size())
            key = keys[i];

        if (channelName.empty())
        {
            server->sendError(client->getFd(), 476, client->getNickname(), channelName);
            continue;
        }
        Channel *channel = server->getChannel(channelName);
        if (!channel)
            channel = server->createChannel(channelName, client);
        else if (channel->isInviteOnly() && channel->getPass() != key)
        {
            server->sendError(client->getFd(), 475, client->getNickname(), channelName);
            continue;
        }
        channel->addClient(client);
        std::string msg = ":" + client->getNickname() + " JOIN " + channelName + "\r\n";
        channel->broadcast(msg, client);
        msg = ":server 332 " + client->getNickname() + " " + channelName + " :" + channel->getTopic() + "\r\n";
        send(client->getFd(), msg.c_str(), msg.length(), 0);
        msg = ":server 353 " + client->getNickname() + " = " + channelName + " :" + channel->getUsers() + "\r\n";
        send(client->getFd(), msg.c_str(), msg.length(), 0);
        msg = ":server 366 " + client->getNickname() + " " + channelName + " :End of /NAMES list\r\n";
        send(client->getFd(), msg.c_str(), msg.length(), 0);
    }
}