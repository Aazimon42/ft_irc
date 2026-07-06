/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:35:18 by edi-maio          #+#    #+#             */
/*   Updated: 2026/06/12 17:36:04 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP
# include <iostream>

class Client
{
    public:
        Client();
        Client(int afd);
        ~Client();
        int getFd(void);
    private:
        int fd;
        std::string nickname;
        std::string username;
};

#endif