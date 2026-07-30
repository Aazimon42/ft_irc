/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 23:47:44 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/31 00:21:23 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

Bot::Bot(int port, const std::string &password, const std::string &nickname, const std::string &channel)
    : _nickname(nickname), _channel(channel)
{
    _sock = socket(AF_INET, SOCK_STREAM, 0);
 
    struct sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(_sock, (struct sockaddr *)&addr, sizeof(addr));
 
    sendRaw("PASS " + password);
    sendRaw("NICK " + nickname);
    sendRaw("USER " + nickname + " 0 * :" + nickname);
    sendRaw("JOIN " + channel);
}
 
void Bot::registerCommands()
{
    _commands["!hello"] = &Bot::cmd_hello;
    _commands["!dice"] = &Bot::cmd_dice;
}
 
void Bot::sendRaw(const std::string &line)
{
    std::string full = line + "\r\n";
    send(_sock, full.c_str(), full.length(), 0);
}
 
void Bot::handleLine(const std::string &line)
{
    if (line.compare(0, 4, "PING") == 0)
    {
        sendRaw("PONG " + line.substr(5));
        return;
    }
    size_t p1 = line.find(' ');
    size_t p2 = line.find(' ', p1 + 1);
    size_t p3 = line.find(' ', p2 + 1);
    
    if (p1 == std::string::npos || p2 == std::string::npos || p3 == std::string::npos)
        return;
    if (line.substr(p1 + 1, p2 - p1 - 1) != "PRIVMSG")
        return;
 
    std::string sender = line.substr(1, line.find('!') - 1);
    std::string target = line.substr(p2 + 1, p3 - p2 - 1);
    std::string message = line.substr(p3 + 2);
    std::string dest = (target[0] == '#') ? target : sender;
 
    std::vector<std::string> args;
    std::stringstream ss(message);
    std::string token;
    while (ss >> token)
        args.push_back(token);
 
    if (args.empty() || sender == _nickname)
        return;
 
    std::map<std::string, Handler>::iterator it = _commands.find(args[0]);
    if (it != _commands.end())
        (this->*it->second)(sender, dest, args);
}
 
void Bot::run()
{
    char buffer[1024];
    while (true)
    {
        ssize_t n = recv(_sock, buffer, sizeof(buffer), 0);
        if (n <= 0)
            break;
        _inBuffer.append(buffer, n);
        size_t pos;
        while ((pos = _inBuffer.find("\r\n")) != std::string::npos)
        {
            handleLine(_inBuffer.substr(0, pos));
            _inBuffer.erase(0, pos + 2);
        }
    }
}

void Bot::cmd_hello(const std::string &sender, const std::string &dest, const std::vector<std::string> &args)
{
    (void)args;
    sendRaw("PRIVMSG " + dest + " :Salut " + sender + " !");
}
 
void Bot::cmd_dice(const std::string &sender, const std::string &dest, const std::vector<std::string> &args)
{
    (void)args;
    std::stringstream ss;
    ss << (std::rand() % 6) + 1;
    sendRaw("PRIVMSG " + dest + " :" + sender + " fait " + ss.str());
}

