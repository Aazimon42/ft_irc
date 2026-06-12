/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:00:01 by edi-maio          #+#    #+#             */
/*   Updated: 2026/06/12 20:52:10 by edi-maio         ###   ########.fr       */
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

struct pollfd
{
    int fd;
    short events;
    short revents;
};

int parsing(char *str);

#endif