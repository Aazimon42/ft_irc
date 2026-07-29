/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivmsgCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/30 00:23:47 by edi-maio         ###   ########.fr       */
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
    if (args.size() < 3)
    {
        server->sendError(client->getFd(), 411, client->getNickname(), "");
        return;
    }
    std::string target = args[1];
    Channel *channel = server->getChannel(target);
    channel->broadcast(":" + client->getNickname() + "!" + client->getUsername() + "@localhost PRIVMSG " + target + " :" + args[2] + "\r\n", client);
}
