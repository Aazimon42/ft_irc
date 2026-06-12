/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:45:06 by edi-maio          #+#    #+#             */
/*   Updated: 2026/06/12 17:56:52 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "irc.hpp"
# include "Client.hpp"

class Channel
{
    public:
        Channel();
        ~Channel();
    private:
        bool invite_only;
        int max_users;
        std::string name;
        std::string topic;
        std::string password;
        std::vector<Client&> operators;
        std::vector<Client&> clients;
};

#endif