/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCommand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/25 00:03:44 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITECOMMAND_HPP
# define INVITECOMMAND_HPP

# include "Command.hpp"
# include "irc.hpp"

class InviteCommand : public Command
{
    public:
        InviteCommand(Server *server, Client *client, std::vector<std::string> args);
        ~InviteCommand();
        void execute();
};

#endif
