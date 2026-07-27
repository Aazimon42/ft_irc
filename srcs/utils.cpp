/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:30:12 by edi-maio          #+#    #+#             */
/*   Updated: 2026/07/27 21:34:12 by edi-maio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <sstream>

std::vector<std::string> split(const std::string &str, char delim)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delim))
        tokens.push_back(token);

    return tokens;
}

std::vector<std::string> parsecmd(const std::string &line)
{
	std::vector<std::string>	tokens;
	size_t						i;
	size_t						start;

	i = 0;
	while (i < line.length())
	{
		while (i < line.length() && line[i] == ' ')
			i++;
		if (i >= line.length())
			break ;
		if (line[i] == ':')
		{
			tokens.push_back(line.substr(i + 1));
			return (tokens);
		}
		start = i;
		while (i < line.length() && line[i] != ' ')
			i++;
		tokens.push_back(line.substr(start, i - start));
	}
	return (tokens);
}