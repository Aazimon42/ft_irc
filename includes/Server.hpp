/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:28:03 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/31 00:47:06 by edi-maio         ###   ########.fr       */
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
# include "Channel.hpp"

class Client;
class Channel;
class Server
{
    public:
        Server(int port, std::string password);
        ~Server();
        void init();
        void run();
        static void handleSignal(int sig);
        void acceptClient();
        void handleClientData(int i);
        Command *handle_input(int i, std::string todo);
        void disconnectClient(int i);
        void disconnectClient(Client *client);
        Client *getClientFromFd(int fd);
        Client *getClientFromNick(std::string name);
        Channel *createChannel(std::string name, Client *creator);
        Channel *getChannel(std::string name);
        std::vector<Channel*> getChannelsByClient(Client *client);
        void sendError(int fd, int errorCode, std::string nick, std::string param);
        std::string get_password();
    private:
        static bool running;
        int fd;
        int port;
        std::string password;
        std::vector<struct pollfd> pollfds;
        std::vector<Client*> clients;
        std::vector<Channel*> channels;
};

#endif