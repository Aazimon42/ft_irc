/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:28:03 by edi-maio          #+#    #+#             */
/*   Updated: 2026/06/27 22:40:14 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include <poll.h>
# include "irc.hpp"
class Server
{
    public:
        Server(int port, std::string password);
        ~Server();
        void init();
        void run();
        void acceptClient();
        void handleClientData(int i);
        void disconnectClient(int i);
        Client *getClientFromFd(int fd);
    private:
        int running;
        int fd;
        int port;
        std::string password;
        std::vector<struct pollfd> pollfds;
        std::vector<Client*> clients;
};

#endif