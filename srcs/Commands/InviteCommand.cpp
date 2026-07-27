/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/27 21:30:29 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/InviteCommand.hpp"
#include "Server.hpp"

InviteCommand::InviteCommand(Server *server, Client *client, std::vector<std::string> args) : Command(server, client, args)
{}

InviteCommand::~InviteCommand()
{}

void InviteCommand::execute()
{
    if (args.size() < 2)
    {
        server->sendError(client->getFd(), 461, client->getUsername(), "INVITE");
        return;
    }
    Client *target = server->getClientFromFd(std::atoi(args[0].c_str()));
    if (!target)
    {
        server->sendError(client->getFd(), 401, client->getUsername(), args[0]);
        return;
    }
    Channel *channel = server->getChannel(args[1]);
    if (!channel)
    {
        server->sendError(client->getFd(), 403, client->getUsername(), args[1]);
        return;
    }
    if (!channel->isInChannel(client))
    {
        server->sendError(client->getFd(), 442, client->getUsername(), args[1]);
        return;
    }
    if (channel->isInChannel(target))
    {
        server->sendError(client->getFd(), 443, client->getUsername(), args[1]);
        return;
    }
    if (channel->isInviteOnly() && !channel->isOperator(client))
    {
        server->sendError(client->getFd(), 482, client->getUsername(), args[1]);
        return;
    }
    channel->addInvited(target);
}
