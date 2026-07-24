/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/24 23:31:51 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/PartCommand.hpp"

PartCommand::PartCommand(Server *server, Client *client, std::vector<std::string> args) : Command(server, client, args)
{}

PartCommand::~PartCommand()
{}

void PartCommand::execute()
{
    (void)server;
    (void)client;
    (void)args;
}
