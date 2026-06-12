/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:18:54 by edi-maio          #+#    #+#             */
/*   Updated: 2026/06/12 17:22:12 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/irc.hpp"

int port_parser(char *str)
{
    int i = 0;
    int nbchar = 0;

    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (0);
        nbchar++;
        i++;
    }
    if (nbchar > 5)
        return (0);
    return (1);
}

int parsing(char *str)
{
    if (!port_parser(str))
    {
        std::cerr << "Error: Invalid port number" << std::endl;
        return (1);
    }
    int port = std::atoi(str);
    if (port < 1024 || port > 65535)
    {
        std::cerr << "Error: Port number must be between 1024 and 65535" << std::endl;
        return (1);
    }
    return (0);
}