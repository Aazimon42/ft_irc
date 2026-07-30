/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 17:08:39 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/30 03:23:03 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include "Channel.hpp"

Client::Client()
{}
Client::Client(int afd, Server *server) : server(server)
{
    this->fd = afd;
    this->registered = false;
    this->nickname = "";
    this->username = "";
    this->password = "";
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

void Client::setPassword(std::string password)
{
    this->password = password;
}

std::string Client::getPassword()
{
    return (this->password);
}

std::string Client::getNickname()
{
    return (this->nickname);
}

void Client::checkRegistration()
{

    if (this->nickname.empty())
    {
        return;
    }
    if (this->username.empty())
    {
        return;
    }
    if (this->registered)
    {
        return;
    }
    if (this->password == this->server->get_password())
    {
        this->registered = true;
        std::string msg = ":server 001 " + this->nickname + " :Welcome to the IRC server!\r\n";
        send(this->fd, msg.c_str(), msg.length(), 0);
    }
    else
    {
        server->sendError(this->fd, 464, this->nickname, "Password incorrect");
        server->disconnectClient(this);
        return;
    }
}