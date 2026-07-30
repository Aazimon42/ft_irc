/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/30 03:51:33 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/NickCommand.hpp"
#include "Server.hpp"

NickCommand::NickCommand(Server *server, Client *client, std::vector<std::string> args) : Command(server, client, args)
{}

NickCommand::~NickCommand()
{}

static bool isValidNickname(const std::string &nick)
{
    if (nick.empty())
        return false;
    if (nick[0] == '#' || nick[0] == '&' || nick[0] == ':')
        return false;
    for (size_t i = 0; i < nick.length(); i++)
    {
        if (isspace(nick[i]))
            return false;
    }
    return true;
}

void NickCommand::execute()
{
    if (args.size() < 2)
    {
        server->sendError(client->getFd(), 431, client->getNickname(), "");
        return;
    }
    std::string newNick = args[1];
    if (!isValidNickname(args[1]))
    {
        server->sendError(client->getFd(), 432, client->getNickname(), args[1]);
        return;
    }
    if (server->getClientFromNick(newNick) != NULL)
    {
        server->sendError(client->getFd(), 433, "*", newNick);
        return;
    }
    client->setNickname(args[1]);
    std::cout << "[NICK] Set nickname to: [" << client->getNickname() << "]" << std::endl;
    client->checkRegistration();
}
