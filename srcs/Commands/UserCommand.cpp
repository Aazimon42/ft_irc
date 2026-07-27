/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/28 01:15:29 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/UserCommand.hpp"
#include "Server.hpp"

UserCommand::UserCommand(Server *server, Client *client, std::vector<std::string> args) : Command(server, client, args)
{}

UserCommand::~UserCommand()
{}

void UserCommand::execute()
{
    if (args.size() < 5)
    {
        server->sendError(client->getFd(), 461, client->getNickname(), "USER");
        return;
    }
    client->setUsername(args[1]);
    std::cout << "[USER] Set username to: [" << client->getUsername() << "]" << std::endl;
    client->checkRegistration();
}
