/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/24 23:31:51 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/PassCommand.hpp"
#include "Server.hpp"

PassCommand::PassCommand(Server *server, Client *client, std::vector<std::string> args) : Command(server, client, args)
{}

PassCommand::~PassCommand()
{}

void PassCommand::execute()
{
    (void)server;
    (void)client;

    if (this->args.size() < 2 || this->args[1].empty())
    {
        server->sendError(client->getFd(), 461, client->getNickname(), "PASS");
        return;
    }
    client->setPassword(this->args[1]);
    client->checkRegistration();

}
