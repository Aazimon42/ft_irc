/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/31 02:55:23 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/ModeCommand.hpp"
#include "Server.hpp"
#include <sstream>

ModeCommand::ModeCommand(Server *server, Client *client, std::vector<std::string> args) : Command(server, client, args)
{}

ModeCommand::~ModeCommand()
{}

void ModeCommand::execute()
{
    if (args.size() < 2)
    {
        server->sendError(client->getFd(), 461, client->getNickname(), "MODE");
        return;
    }
    Channel *channel = server->getChannel(args[1]);
    if (channel == NULL)
    {
        server->sendError(client->getFd(), 403, client->getNickname(), args[1]);
        return;
    }
    if (!channel->isInChannel(client))
    {
        server->sendError(client->getFd(), 442, client->getNickname(), channel->getName());
        return;
    }
    if (args.size() == 2)
    {
        std::string modes = "+";
        std::string params;

        if (channel->isInviteOnly())
            modes += "i";
        if (channel->isRestrictedTopic())
            modes += "t";
        if (!channel->getPass().empty())
        {
            modes += "k";
            params += " " + channel->getPass();
        }
        if (channel->getMaxUsers() > 0)
        {
            std::ostringstream oss;
            oss << channel->getMaxUsers();
            modes += "l";
            params += " " + oss.str();
        }
        std::string msg = ":server 324 " + client->getNickname()
                        + " " + channel->getName() + " " + modes + params + "\r\n";
        send(client->getFd(), msg.c_str(), msg.length(), 0);
        return;
    }
    if (!channel->isOperator(client))
    {
        server->sendError(client->getFd(), 482, client->getNickname(), channel->getName());
        return;
    }
    if (args[2].empty() || (args[2][0] != '+' && args[2][0] != '-'))
    {
        server->sendError(client->getFd(), 472, client->getNickname(), args[2].substr(0, 1));
        return;
    }
    bool ispos = (args[2][0] == '+');
    unsigned int i = 1;
    std::string appliedModes;
    std::string appliedParams;
    char lastSign = 0;
    while (i < args[2].length())
    {
        std::string usedParam;

        if (args[2][i] == '+' || args[2][i] == '-')
        {
            ispos = (args[2][i] == '+');
            i++;
            continue;
        }
        if (args[2][i] == 'i')
        {
            if (ispos)
            {
                channel->setInviteOnly(true);
            }
            else
            {
                channel->setInviteOnly(false);
            }
        } else if (args[2][i] == 't')
        {
            if (ispos)
            {
                channel->setRestrictedTopic(true);
            }
            else
            {
                channel->setRestrictedTopic(false);
            }
        } else if (args[2][i] == 'k')
        {
            if (ispos)
            {
                if (args.size() < 4 || args[3].empty())
                {
                    server->sendError(client->getFd(), 461, client->getNickname(), "MODE");
                    i++;
                    continue;
                }
                usedParam = args[3];
                channel->setPass(args[3]);
                args.erase((args.begin() + 3));
            }
            else
            {
                channel->setPass("");
            }
        } else if (args[2][i] == 'o')
        {
            if (args.size() < 4 || args[3].empty())
            {
                server->sendError(client->getFd(), 461, client->getNickname(), "MODE");
                i++;
                continue;
            }
            Client *targetClient = server->getClientFromNick(args[3]);
            if (targetClient == NULL)
            {
                server->sendError(client->getFd(), 401, client->getNickname(), args[3]);
                args.erase((args.begin() + 3));
                i++;
                continue;
            }
            if (!channel->isInChannel(targetClient))
            {
                server->sendError(client->getFd(), 441, client->getNickname(), args[3]);
                args.erase((args.begin() + 3));
                i++;
                continue;
            }
            usedParam = args[3];
            if (ispos)
            {
                channel->addOperator(targetClient);
            }
            else
            {
                channel->removeOperator(targetClient);
            }
            args.erase((args.begin() + 3));
        } else if (args[2][i] == 'l')
        {
            if (ispos)
            {
                if (args.size() < 4)
                {
                    server->sendError(client->getFd(), 461, client->getNickname(), "MODE");
                    i++;
                    continue;
                }
                usedParam = args[3];
                int limit = std::atoi(args[3].c_str());
                channel->setMaxUsers(limit);
                args.erase((args.begin() + 3));
            }
            else
            {
                channel->setMaxUsers(0);
            }
        } else
        {
            server->sendError(client->getFd(), 472, client->getNickname(), args[2].substr(i, 1));
            i++;
            continue;
        }

        char sign = (ispos ? '+' : '-');
        if (sign != lastSign)
        {
            appliedModes += sign;
            lastSign = sign;
        }
        appliedModes += args[2][i];
        if (!usedParam.empty())
            appliedParams += " " + usedParam;
        i++;
    }
    if (!appliedModes.empty())
    {
        std::string msg = ":" + client->getNickname() + "!" + client->getUsername() + "@localhost MODE " + channel->getName()
                        + " " + appliedModes + appliedParams + "\r\n";
        channel->broadcast(msg, NULL);
    }
}