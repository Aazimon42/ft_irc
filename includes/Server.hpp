/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:28:03 by edi-maio          #+#    #+#             */
/*   Updated: 2026/06/12 20:51:04 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "irc.hpp"
# include "Client.hpp"

class Server
{
    public:
        Server(int port, std::string password);
        ~Server();
        void start();
        void run();
    private:
        int running;
        int fd;
        int port;
        std::string password;
        std::vector<struct pollfd> pollfds;
        std::vector<Client&> clients;
};

#endif