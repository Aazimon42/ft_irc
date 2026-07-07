/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:45:06 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/06 17:11:01 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "irc.hpp"
# include "Client.hpp"

class Channel
{
    public:
        Channel(std::string name, Client* creator);
        ~Channel();
        void addOperator(Client* client);
        void removeOperator(Client* client);
        void broadcast(const std::string& message, Client* sender);
    private:
        bool invite_only;
        bool restricted_topic;
        int max_users;
        std::string name;
        std::string topic;
        std::string password;
        std::vector<Client*> operators;
        std::vector<Client*> clients;
};

#endif