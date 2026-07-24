/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/24 23:31:51 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/NickCommand.hpp"

NickCommand::NickCommand(Server *server, Client *client, std::vector<std::string> args) : Command(server, client, args)
{}

NickCommand::~NickCommand()
{}

void NickCommand::execute()
{
    (void)server;
    (void)client;
    (void)args;
}
