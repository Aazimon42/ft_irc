/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:45:06 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/30 03:06:26 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "irc.hpp"
# include "Client.hpp"

class Channel
{
    public:
        Channel(std::string name, Client *creator);
        ~Channel();
        void addClient(Client *client);
        void removeClient(Client *client);
        void addOperator(Client *client);
        void removeOperator(Client *client);
        void addInvited(Client *client);
        void broadcast(const std::string& message, Client *sender);
        std::string getPass();
        std::string getName();
        std::string getTopic();
        std::string getUsers();
        bool isInviteOnly();
        bool isRestrictedTopic();
        bool isOperator(Client *client);
        bool isInChannel(Client *client);
        void setTopic(std::string topic);
    private:
        bool invite_only;
        bool restricted_topic;
        int max_users;
        std::string name;
        std::string topic;
        std::string password;
        std::vector<Client*> operators;
        std::vector<Client*> clients;
        std::vector<Client*> invited;
};

#endif