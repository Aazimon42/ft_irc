/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:11:40 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/08 17:41:32 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/JoinCommand.hpp"

JoinCommand::JoinCommand(Server *server, Client *client, std::vector<std::string> args) : Command(server, client, args)
{}

JoinCommand::~JoinCommand()
{}

void JoinCommand::execute()
{
    if (args.empty())
        return;

    std::vector<std::string> channels = split(args[0], ',');
    std::vector<std::string> keys;

    if (args.size() > 1)
        keys = split(args[1], ',');

    for (size_t i = 0; i < channels.size(); ++i)
    {
        std::string channel = channels[i];
        std::string key;
        if (i < keys.size())
            key = keys[i];
        client->join(channel, key);
    }
}