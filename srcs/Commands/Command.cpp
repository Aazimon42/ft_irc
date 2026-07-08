/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:21:56 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/08 17:25:04 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Command.hpp"

Command::Command(Server *server, Client *client, std::vector<std::string> args)
{
    this->server = server;
    this->client = client;
    this->args = args;
}

Command::~Command()
{}