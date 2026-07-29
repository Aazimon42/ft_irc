/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCommand.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/30 00:45:42 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/PassCommand.hpp"

PassCommand::PassCommand(Server *server, Client *client, std::vector<std::string> args) : Command(server, client, args)
{}

PassCommand::~PassCommand()
{}

void PassCommand::execute()
{
    std::cout << "[PASS] Password sent: [" << args[1] << "]" << std::endl;
}
