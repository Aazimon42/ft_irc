/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/08/03 18:08:33 by edi-maio         ###   ########.fr       */
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
    if (this->args.size() < 2 || this->args[1].empty())
    {
        server->sendError(client->getFd(), 461, client->getNickname(), "PASS");
        return;
    }
    std::cout << "[PASS] received password:" << args[1] << std::endl;
    client->setPassword(this->args[1]);
}
