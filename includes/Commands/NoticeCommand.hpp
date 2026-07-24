/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NoticeCommand.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 00:00:00 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/25 00:03:44 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOTICECOMMAND_HPP
# define NOTICECOMMAND_HPP

# include "Command.hpp"
# include "irc.hpp"

class NoticeCommand : public Command
{
    public:
        NoticeCommand(Server *server, Client *client, std::vector<std::string> args);
        ~NoticeCommand();
        void execute();
};

#endif
