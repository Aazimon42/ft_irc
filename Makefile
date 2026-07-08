# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edi-maio <edi-maio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/10 00:00:50 by edi-maio          #+#    #+#              #
#    Updated: 2026/07/08 17:22:13 by edi-maio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CPP=c++
CPPFLAGS = -Wall -Werror -Wextra -g -std=c++98
NAME = ircserv
INC_DIR = includes/
SRC_DIR = srcs/
SRCS = $(SRC_DIR)main.cpp \
		$(SRC_DIR)Client.cpp \
		$(SRC_DIR)Server.cpp \
		$(SRC_DIR)parsing.cpp \
		$(SRC_DIR)utils.cpp \
		$(SRC_DIR)Channel.cpp \
		$(SRC_DIR)Commands/Command.cpp \
		$(SRC_DIR)Commands/JoinCommand.cpp

OBJ_DIR = objs/
OBJS = $(SRCS:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -I $(INC_DIR) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) -I $(INC_DIR) $< -c -o $@

fclean: clean
	rm -f $(NAME)

clean:
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all fclean clean re