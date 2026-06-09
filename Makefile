# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/10 00:00:50 by edi-maio          #+#    #+#              #
#    Updated: 2026/06/10 00:02:24 by edi-maio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPP=c++
CPPFLAGS = -Wall -Werror -Wextra -g -std=c++98
NAME = webserv
SRC_DIR = srcs/
SRCS = $(SRC_DIR)main.cpp

OBJ_DIR = objs/
OBJS = $(SRCS:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) $< -c -o $@

fclean: clean
	rm -f $(NAME)

clean:
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all fclean clean re