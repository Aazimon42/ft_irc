/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/30 02:30:09 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/NickCommand.hpp"
#include "Server.hpp"

NickCommand::NickCommand(Server *server, Client *client, std::vector<std::string> args) : Command(server, client, args)
{}

NickCommand::~NickCommand()
{}

void NickCommand::execute()
{
    if (args.size() < 2)
    {
        server->sendError(client->getFd(), 431, client->getNickname(), "");
        return;
    }
    std::string newNick = args[1];
    if (server->getClientFromNick(newNick) != NULL)
    {
        server->sendError(client->getFd(), 433, "*", newNick);
        return;
    }
    client->setNickname(args[1]);
    std::cout << "[NICK] Set nickname to: [" << client->getNickname() << "]" << std::endl;
    client->checkRegistration();
}
