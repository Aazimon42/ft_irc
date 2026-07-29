/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:10:07 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/08 17:18:44 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "Client.hpp"
# include <vector>

class Server;
class Client;
class Command
{
    public:
        Command(Server *server, Client *client, std::vector<std::string> args);
        virtual ~Command();
        virtual void execute() = 0;
    protected:
        Server *server;
        Client *client;
        std::vector<std::string> args;
};

#endif