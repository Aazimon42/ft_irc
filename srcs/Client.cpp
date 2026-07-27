/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:08:39 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/28 01:16:03 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include "Channel.hpp"

Client::Client()
{}
Client::Client(int afd)
{
    this->fd = afd;
    this->nickname = "";
    this->username = "";
}

Client::~Client()
{}

int Client::getFd()
{
    return (this->fd);
}

void Client::setNickname(std::string nickname)
{
    this->nickname = nickname;
}

void Client::setUsername(std::string username)
{
    this->username = username;
}

std::string Client::getUsername()
{
    return (this->username);
}

std::string Client::getNickname()
{
    return (this->nickname);
}

void Client::checkRegistration()
{
    if (!this->nickname.empty() && !this->username.empty() && !this->registered)
    {
        this->registered = true;
        std::string msg = ":server 001 " + this->nickname + " :Welcome to the IRC server, "
            + this->nickname + "!" + this->username + "@localhost\r\n";
        send(this->fd, msg.c_str(), msg.length(), 0);
    }
}