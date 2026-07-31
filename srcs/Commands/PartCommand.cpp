/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/31 01:51:08 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/PartCommand.hpp"
#include "Server.hpp"

PartCommand::PartCommand(Server *server, Client *client, std::vector<std::string> args) : Command(server, client, args)
{}

PartCommand::~PartCommand()
{}

void PartCommand::execute()
{
    if (args.size() < 2)
    {
        server->sendError(client->getFd(), 461, client->getNickname(), "PART");
        return;
    }
    std::string reason = "Leaving";
    if (args.size() == 3)
        reason = args[2];
    std::vector<std::string> channels = split(args[1], ',');
    for (size_t i = 0; i < channels.size(); ++i)
    {
        std::string channelName = channels[i];
        if (channelName.empty())
        {
            server->sendError(client->getFd(), 476, client->getNickname(), channelName);
            continue;
        }
        Channel *channel = server->getChannel(channelName);
        if (!channel)
        {
            server->sendError(client->getFd(), 403, client->getNickname(), channelName);
            continue;
        }
        if (!channel->isInChannel(client))
        {
            server->sendError(client->getFd(), 442, client->getNickname(), channelName);
            continue;
        }
        std::string partMsg = ":" + client->getNickname() + "!" + client->getUsername() 
            + "@localhost PART " + channelName + " :" + reason + "\r\n";
        channel->broadcast(partMsg, NULL);
        channel->removeClient(client);
    }
}
