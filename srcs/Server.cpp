/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:31:13 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/27 21:19:13 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, std::string password)
{
    this->running = 0;
    this->port = port;
    this->password = password;
}
Server::~Server()
{}
void Server::init()
{
    this->running = 1;
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
        throw IrcException("Error: Failed to create socket");
    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        throw IrcException("Error: Failed to bind socket");
    if (listen(fd, 16) < 0)
		throw IrcException("Error: Failed to listen on socket");
    if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
        throw IrcException("Error: Failed to set non-blocking");
    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    this->pollfds.push_back(pfd);
}

void Server::run()
{
    while (running)
    {
        if (poll(&pollfds[0], pollfds.size(), -1) < 0)
		{
            throw IrcException("Error: Failed to Poll");
		}
        for (unsigned long i = 0; i < pollfds.size(); i++)
        {
            if (pollfds[i].revents & POLLIN)
            {
                if (pollfds[i].fd == this->fd)
                    acceptClient();
                else
                    handleClientData(i);
            }
            if (pollfds[i].revents & (POLLHUP | POLLERR))
                disconnectClient(i);
        }
    }
}

void Server::acceptClient()
{
    int client_fd = accept(this->fd, NULL, NULL);
    if (client_fd < 0)  
        return ;
    fcntl(client_fd, F_SETFL, O_NONBLOCK);
    Client *client = new Client(client_fd);
    this->clients.push_back(client);
        struct pollfd pfd;
    pfd.fd = client_fd;
    pfd.events = POLLIN;
    pfd.revents = 0;
    this->pollfds.push_back(pfd);
    std::cout << "nouveau client"<< std::endl;
}

void Server::handleClientData(int i)
{
    char buffer[512];
    std::memset(buffer, 0, sizeof(buffer));

    int n = recv(pollfds[i].fd, buffer, sizeof(buffer) - 1, 0);

    if (n <= 0)
    {
        disconnectClient(i);
        return ;
    }
    buffer[n] = '\0';
    handle_input(i, buffer);
    std::cout << "Received from fd " << pollfds[i].fd << ": " << buffer;
}

Command *Server::handle_input(int i, char *buffer)
{
    std::string commands[12] = {"JOIN", "PASS", "NICK", "USER", "QUIT", "PRIVMSG", "NOTICE", "MODE", "TOPIC", "INVITE", "KICK", "PART"};
    int command = 0;
    Client *client = getClientFromFd(pollfds[i].fd);
    std::vector<std::string> args = split(buffer, ' ');
    while (command < 12)
    {
        if (commands[command] == buffer)
            break;
        command++;
    }
    switch (command)
    {
        case (0):
            return new JoinCommand(this, client, args);
        case (1):
            return new PassCommand(this, client, args);
        case (2):
            return new NickCommand(this, client, args);
        case (3):
            return new UserCommand(this, client, args);
        case (4):
            return new QuitCommand(this, client, args);
        case (5):
            return new PrivmsgCommand(this, client, args);
        case (6):
            return new NoticeCommand(this, client, args);
        case (7):
            return new ModeCommand(this, client, args);
        case (8):
            return new TopicCommand(this, client, args);
        case (9):
            return new InviteCommand(this, client, args);
        case (10):
            return new KickCommand(this, client, args);
        case (11):
            return new PartCommand(this, client, args);
        default:
            std::cout << "Unknown command: " << command << std::endl;
            return (NULL);
    }
}

Client *Server::getClientFromFd(int fd)
{
    for (size_t i = 0; i < clients.size(); i++)
    {
        if (clients[i]->getFd() == fd)
            return clients[i];
    }
    return NULL;
}

Channel *Server::getChannel(std::string name)
{
    for (size_t i = 0; i < channels.size(); i++)
    {
        if (channels[i]->getName() == name)
            return channels[i];
    }
    return NULL;
}

void Server::disconnectClient(int i)
{
    int client_fd = pollfds[i].fd;
    close(client_fd);

    for (size_t j = 0; j < clients.size(); j++)
    {
        if (clients[j]->getFd() == client_fd)
        {
            delete clients[j];
            clients.erase(clients.begin() + j);
            break;
        }
    }
    pollfds.erase(pollfds.begin() + i);
}

#include <sstream>

std::string intToString(int nb)
{
    std::stringstream ss;
    ss << nb;
    return ss.str();
}

void Server::sendError(int fd, int errorCode, std::string nick, std::string param)
{
    std::string msg;

    switch (errorCode)
    {
        case 401:
            msg = param + " :No such nick/channel";
            break;
        case 403:
            msg = param + " :No such channel";
            break;
        case 404:
            msg = param + " :Cannot send to channel";
            break;
        case 411:
            msg = ":No recipient given";
            break;
        case 412:
            msg = ":No text to send";
            break;
        case 421:
            msg = param + " :Unknown command";
            break;
        case 431:
            msg = ":No nickname given";
            break;
        case 432:
            msg = param + " :Erroneous nickname";
            break;
        case 433:
            msg = param + " :Nickname is already in use";
            break;
        case 441:
            msg = param + " :They aren't on that channel";
            break;
        case 442:
            msg = param + " :You're not on that channel";
            break;
        case 443:
            msg = param + " :is already on channel";
            break;
        case 451:
            msg = ":You have not registered";
            break;
        case 461:
            msg = param + " :Not enough parameters";
            break;
        case 462:
            msg = ":You may not reregister";
            break;
        case 463:
            msg = ":Your host isn't among the privileged";
            break;
        case 464:
            msg = ":Password incorrect";
            break;
        case 471:
            msg = param + " :Cannot join channel (+l)";
            break;
        case 472:
            msg = param + " :is unknown mode char to me";
            break;
        case 473:
            msg = param + " :Cannot join channel (+i)";
            break;
        case 474:
            msg = param + " :Cannot join channel (+b)";
            break;
        case 475:
            msg = param + " :Cannot join channel (+k)";
            break;
        case 476:
            msg = param + " :Bad Channel Mask";
            break;
        case 481:
            msg = ":Permission Denied- You're not an IRC operator";
            break;
        case 482:
            msg = param + " :You're not channel operator";
            break;
        default:
            msg = ":Unknown error";
            break;
    }
    std::string full = ":server " + intToString(errorCode) + " " + nick + " " + msg + "\r\n";
    send(fd, full.c_str(), full.length(), 0);
}