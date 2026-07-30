/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/30 03:15:11 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/PrivmsgCommand.hpp"
#include "Server.hpp"

PrivmsgCommand::PrivmsgCommand(Server *server, Client *client, std::vector<std::string> args) : Command(server, client, args)
{}

PrivmsgCommand::~PrivmsgCommand()
{}

void PrivmsgCommand::execute()
{
    if (args.size() < 2)
    {
        server->sendError(client->getFd(), 411, client->getNickname(), "");
        return;
    }
    if (args.size() < 3 || args[2].empty())
    {
        server->sendError(client->getFd(), 412, client->getNickname(), "");
        return;
    }
    std::string target = args[1];
    Channel *channel = server->getChannel(target);
    if (channel)
    {
        if (channel->isInChannel(client) == false)
        {
            server->sendError(client->getFd(), 404, client->getNickname(), target);
            return;
        }
        std::string message = ":" + client->getNickname() + "!" + client->getUsername() 
            + "@localhost PRIVMSG " + target + " :" + args[2] + "\r\n";
        channel->broadcast(message, client);
    }
    else
    {
        Client *targetClient = server->getClientFromNick(target);
        if (targetClient == NULL)
        {
            server->sendError(client->getFd(), 401, client->getNickname(), target);
            return;
        }
        std::string message = ":" + client->getNickname() + "!" + client->getUsername() 
            + "@localhost PRIVMSG " + target + " :" + args[2] + "\r\n";
        send(targetClient->getFd(), message.c_str(), message.length(), 0);
    }
}
