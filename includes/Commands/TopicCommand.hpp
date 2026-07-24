/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCommand.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/24 23:31:51 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPICCOMMAND_HPP
# define TOPICCOMMAND_HPP

# include "Command.hpp"
# include "irc.hpp"

class TopicCommand : public Command
{
    public:
        TopicCommand(Server *server, Client *client, std::vector<std::string> args);
        ~TopicCommand();
        void execute();
};

#endif
