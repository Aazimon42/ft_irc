/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:28:03 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/08 17:17:42 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include <poll.h>
# include "irc.hpp"
# include "Commands/Command.hpp"
# include "Commands/JoinCommand.hpp"
# include "Channel.hpp"

class Server
{
    public:
        Server(int port, std::string password);
        ~Server();
        void init();
        void run();
        void acceptClient();
        void handleClientData(int i);
        Command *handle_input(int i, char *buffer);
        void disconnectClient(int i);
        Client *getClientFromFd(int fd);
        Channel *getChannel(std::string name);
    private:
        int running;
        int fd;
        int port;
        std::string password;
        std::vector<struct pollfd> pollfds;
        std::vector<Client*> clients;
        std::vector<Channel*> channels;
};

#endif