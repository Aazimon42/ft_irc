/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:28:03 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/27 21:18:58 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include <poll.h>
# include "irc.hpp"
# include "Commands/Command.hpp"
# include "Commands/JoinCommand.hpp"
# include "Commands/PassCommand.hpp"
# include "Commands/ModeCommand.hpp"
# include "Commands/TopicCommand.hpp"
# include "Commands/UserCommand.hpp"
# include "Commands/NickCommand.hpp"
# include "Commands/PrivmsgCommand.hpp"
# include "Commands/PartCommand.hpp"
# include "Commands/QuitCommand.hpp"
# include "Commands/InviteCommand.hpp"
# include "Commands/KickCommand.hpp"
# include "Commands/NoticeCommand.hpp"
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
        void Server::sendError(int fd, int errorCode, std::string nick, std::string param);
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