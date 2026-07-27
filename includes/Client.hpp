/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:35:18 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/28 00:35:11 by edi-maio         ###   ########.fr       */
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
        Client(int afd);
        ~Client();
        int getFd(void);
        std::string getUsername(void);
    private:
        int fd;
        std::string nickname;
        std::string username;
        Server *server;
};

#endif