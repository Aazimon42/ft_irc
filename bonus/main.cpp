/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 23:58:24 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/31 00:14:08 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        std::cerr << "Usage: " << argv[0] << " <port> <password> <channel>" << std::endl;
        return 1;
    }
    Bot bot(std::atoi(argv[1]), argv[2], "Bot", argv[3]);
    bot.registerCommands();
    bot.run();
    return 0;
}
