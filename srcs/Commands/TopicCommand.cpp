/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCommand.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/30 03:25:23 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/TopicCommand.hpp"
#include "Server.hpp"

TopicCommand::TopicCommand(Server *server, Client *client, std::vector<std::string> args) : Command(server, client, args)
{}

TopicCommand::~TopicCommand()
{}

void TopicCommand::execute()
{
    if (args.size() < 2)
    {
        server->sendError(client->getFd(), 461, client->getNickname(), "TOPIC");
        return;
    }
    Channel *channel = server->getChannel(args[1]);
    if (!channel)
    {
        server->sendError(client->getFd(), 403, client->getNickname(), args[1]);
        return;
    }
    if (!channel->isInChannel(client))
    {
        server->sendError(client->getFd(), 442, client->getNickname(), args[1]);
        return;
    }
    if (args.size() == 2)
    {
        std::string msg;
        if (channel->getTopic().empty())
            msg = ":server 331 " + client->getNickname() + " " + args[1] + " :No topic is set\r\n";
        else
            msg = ":server 332 " + client->getNickname() + " " + args[1] + " :" + channel->getTopic() + "\r\n";
        send(client->getFd(), msg.c_str(), msg.length(), 0);
        return;
    }
    if (channel->isRestrictedTopic() && !channel->isOperator(client))
    {
        server->sendError(client->getFd(), 482, client->getNickname(), args[1]);
        return;
    }
    channel->setTopic(args[2]);
    std::string msg = ":" + client->getNickname() + "!" + client->getUsername() 
        + "@localhost TOPIC " + args[1] + " :" + args[2] + "\r\n";
    channel->broadcast(msg, NULL);
}
