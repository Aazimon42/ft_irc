/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 23:47:58 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/31 00:13:46 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include <string>
# include <vector>
# include <map>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <cstring>
# include <cstdlib>
# include <sstream>

class Bot
{
    private:
        int _sock;
        std::string _nickname;
        std::string _channel;
        std::string _inBuffer;
        typedef void (Bot::*Handler)(const std::string &sender, const std::string &dest, const std::vector<std::string> &args);
        std::map<std::string, Handler> _commands;
        void sendRaw(const std::string &line);
        void handleLine(const std::string &line);
        void cmd_hello(const std::string &sender, const std::string &dest, const std::vector<std::string> &args);
        void cmd_dice(const std::string &sender, const std::string &dest, const std::vector<std::string> &args);
    public:
        Bot(int port, const std::string &password, const std::string &nickname, const std::string &channel);
        void registerCommands();
        void run();  
};

#endif