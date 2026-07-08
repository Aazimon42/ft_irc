/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:09:51 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/08 17:19:22 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINCOMMAND_HPP
# define JOINCOMMAND_HPP

# include "Command.hpp"
# include "irc.hpp"

class JoinCommand : public Command
{
    public:
        JoinCommand(Server *server, Client *client, std::vector<std::string> args);
        ~JoinCommand();
        void execute();
};

#endif