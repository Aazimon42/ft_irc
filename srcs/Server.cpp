/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:31:13 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/31 01:28:53 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sstream>
#include "Server.hpp"
#include "Client.hpp"

bool Server::running = false;

Server::Server(int port, std::string password)
{
    this->port = port;
    this->password = password;
}
Server::~Server()
{
    while (!clients.empty())
        disconnectClient(clients[0]);
    for (std::vector<Channel*>::iterator it = channels.begin(); it != channels.end(); it++)
        delete *it;
    close (fd);
}
void Server::init()
{
    Server::running = true;
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

void Server::handleSignal(int sig)
{
    (void)sig;
    Server::running = false;
}

void Server::acceptClient()
{
    int client_fd = accept(this->fd, NULL, NULL);
    if (client_fd < 0)  
        return ;
    fcntl(client_fd, F_SETFL, O_NONBLOCK);
    Client *client = new Client(client_fd, this);
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
	char	buffer[512];
	ssize_t	n;
	std::string	line;
	size_t		pos;
    int fd = pollfds[i].fd;

	n = recv(pollfds[i].fd, buffer, sizeof(buffer), 0);
	if (n <= 0)
	{
		disconnectClient(i);
		return ;
	}
	std::cout << "Received from fd " << pollfds[i].fd << ": " << std::string(buffer, n);
	Client *client = getClientFromFd(pollfds[i].fd);
	if (!client)
		return ;
	client->_inBuffer.append(buffer, n);
	while ((pos = client->_inBuffer.find('\n')) != std::string::npos)
	{
		line = client->_inBuffer.substr(0, pos);
		client->_inBuffer.erase(0, pos + 1);
		if (!line.empty() && line[line.length() - 1] == '\r')
			line.erase(line.length() - 1);
		if (!line.empty())
        {
			Command *command = handle_input(i, line);
            if (command)
            {
                command->execute();
                delete command;
            }
            if (!getClientFromFd(fd))
                return;
        }
	}
}

std::string Server::get_password()
{
    return this->password;
}

Command *Server::handle_input(int i, std::string todo)
{
    std::string commands[11] = {"JOIN", "PASS", "NICK", "USER", "QUIT", "PRIVMSG", "MODE", "TOPIC", "INVITE", "KICK", "PART"};
    int command = 0;
    Client *client = getClientFromFd(pollfds[i].fd);
    std::vector<std::string> args = parsecmd(todo);
    unsigned long j = 0;
    while (j < args.size())
    {
        std::cout << "ARG " << j << " = " << args[j] << std::endl; 
        j++;
    }
    while (command < 11)
    {
        if (commands[command] == args[0])
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
            return new ModeCommand(this, client, args);
        case (7):
            return new TopicCommand(this, client, args);
        case (8):
            return new InviteCommand(this, client, args);
        case (9):
            return new KickCommand(this, client, args);
        case (10):
            return new PartCommand(this, client, args);
        default:
            std::cout << "Unknown command :"  << args[0] << std::endl;
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

Client *Server::getClientFromNick(std::string name)
{
    for (size_t i = 0; i < clients.size(); i++)
    {
        if (clients[i]->getNickname() == name)
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

Channel *Server::createChannel(std::string name, Client *creator)
{
    Channel *channel = new Channel(name, creator);
    channels.push_back(channel);
    return (channel);
}

std::vector<Channel*> Server::getChannelsByClient(Client *client)
{
    std::vector<Channel*> clientChannels;
    for (size_t i = 0; i < channels.size(); i++)
    {
        if (channels[i]->isInChannel(client))
            clientChannels.push_back(channels[i]);
    }
    return clientChannels;
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

void Server::disconnectClient(Client *client)
{
    int client_fd = client->getFd();

    close(client_fd);
    for (size_t i = 0; i < pollfds.size(); i++)
    {
        if (pollfds[i].fd == client_fd)
        {
            pollfds.erase(pollfds.begin() + i);
            break;
        }
    }
    for (size_t j = 0; j < clients.size(); j++)
    {
        if (clients[j] == client)
        {
            clients.erase(clients.begin() + j);
            break;
        }
    }
    delete client;
}

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