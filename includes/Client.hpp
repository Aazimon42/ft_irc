/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:35:18 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/28 01:14:46 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>

class Channel;
class Server;

class Client
{
    public:
        std::string _inBuffer;
        Client();
        Client(int afd, Server *server);
        ~Client();
        int getFd(void);
        void setNickname(std::string nickname);
        void setUsername(std::string username);
        std::string getUsername(void);
        std::string getNickname(void);
        void checkRegistration();
        void setPassword(std::string password);
        std::string getPassword(void);
    private:
        int fd;
        bool registered;
        std::string nickname;
        std::string username;
        std::string password;
        Server *server;
};

#endif