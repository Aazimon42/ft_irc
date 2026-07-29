/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/30 01:21:31 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/QuitCommand.hpp"
#include "Server.hpp"

QuitCommand::QuitCommand(Server *server, Client *client, std::vector<std::string> args) : Command(server, client, args)
{}

QuitCommand::~QuitCommand()
{}

void QuitCommand::execute()
{
    std::string quitMessage = "Client " + client->getNickname() + " has left the server.";
    if (args.size() == 2)
        quitMessage = args[1];
    std::string msg = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost QUIT :" + quitMessage + "\r\n";
    std::vector<Channel*> clientChannels = server->getChannelsByClient(client);
    for (std::vector<Channel*>::iterator it = clientChannels.begin(); it != clientChannels.end(); ++it)
    {
        Channel *channel = *it;
        channel->broadcast(msg, client);
        channel->removeClient(client);
    }
    //server->disconnectClient(client);
}