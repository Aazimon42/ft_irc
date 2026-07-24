/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCommand.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/24 23:31:51 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTCOMMAND_HPP
# define PARTCOMMAND_HPP

# include "Command.hpp"
# include "irc.hpp"

class PartCommand : public Command
{
    public:
        PartCommand(Server *server, Client *client, std::vector<std::string> args);
        ~PartCommand();
        void execute();
};

#endif
