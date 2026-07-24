/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/25 00:03:44 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/InviteCommand.hpp"

InviteCommand::InviteCommand(Server *server, Client *client, std::vector<std::string> args) : Command(server, client, args)
{}

InviteCommand::~InviteCommand()
{}

void InviteCommand::execute()
{
    (void)server;
    (void)client;
    (void)args;
}
