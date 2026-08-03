/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 17:45:06 by edi-maio          #+#    #+#             */
/*   Updated: 2026/08/03 18:06:59 by edi-maio         ###   ########.fr       */
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
        void setPass(std::string pass);
        void setMaxUsers(int max);
        void setInviteOnly(bool invite_only);
        void setRestrictedTopic(bool restricted_topic);
        bool isInviteOnly();
        bool isRestrictedTopic();
        bool isOperator(Client *client);
        bool isInChannel(Client *client);
        bool isInvited(Client *client);
        void setTopic(std::string topic);
        int getMaxUsers();
        int getClientCount();
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