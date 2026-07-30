/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/30 02:50:46 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/KickCommand.hpp"
#include "Server.hpp"

KickCommand::KickCommand(Server *server, Client *client, std::vector<std::string> args) : Command(server, client, args)
{}

KickCommand::~KickCommand()
{}

void KickCommand::execute()
{
    if (args.size() < 3)
    {
        server->sendError(client->getFd(), 461, client->getNickname(), "KICK");
        return;
    }
    Channel *channel = server->getChannel(args[1]);
    if (channel == NULL)
    {
        server->sendError(client->getFd(), 403, client->getNickname(), args[1]);
        return;
    }
    if (channel->isInChannel(client) == false)
    {
        server->sendError(client->getFd(), 442, client->getNickname(), args[1]);
        return;
    }
    if (channel->isOperator(client) == false)
    {
        server->sendError(client->getFd(), 482, client->getNickname(), args[1]);
        return;
    }
    if (channel->isInChannel(server->getClientFromNick(args[2])) == false)
    {
        server->sendError(client->getFd(), 441, client->getNickname(), args[2]);
        return;
    }
    std::string message = ":" + client->getNickname() + " KICK " + args[1] + " " + args[2] + " :" + args[3] + "\r\n";
    send(client->getFd(), message.c_str(), message.length(), 0);
    channel->broadcast(message, client);
    channel->removeClient(server->getClientFromNick(args[2]));
}
