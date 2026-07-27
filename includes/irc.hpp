/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:00:01 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/08 16:31:19 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
# define IRC_HPP

# include <iostream>
# include <string>
# include <unistd.h>
# include <cstring>
# include <poll.h>
# include <fcntl.h>
# include <vector>
# include <sys/socket.h>
# include <netinet/in.h>
# include <cstdlib>

class IrcException : public std::exception
{
    private:
        std::string msg;
    public:
        IrcException(std::string const &msg) : msg(msg) {}
        ~IrcException() throw() {}
        const char *what() const throw() { return msg.c_str(); }
};
int parsing(char *str);
std::vector<std::string> split(const std::string &str, char delim);
std::vector<std::string> parsecmd(const std::string &line);

#endif