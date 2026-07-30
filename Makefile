CPP=c++
CPPFLAGS = -Wall -Werror -Wextra -g -std=c++98
NAME = ircserv
INC_DIR = includes/
SRC_DIR = srcs/
OBJ_DIR = objs/

SRCS = $(SRC_DIR)main.cpp \
		$(SRC_DIR)Client.cpp \
		$(SRC_DIR)Server.cpp \
		$(SRC_DIR)parsing.cpp \
		$(SRC_DIR)utils.cpp \
		$(SRC_DIR)Channel.cpp \
		$(SRC_DIR)Commands/Command.cpp \
		$(SRC_DIR)Commands/JoinCommand.cpp \
		$(SRC_DIR)Commands/PassCommand.cpp \
		$(SRC_DIR)Commands/NickCommand.cpp \
		$(SRC_DIR)Commands/UserCommand.cpp \
		$(SRC_DIR)Commands/QuitCommand.cpp \
		$(SRC_DIR)Commands/PrivmsgCommand.cpp \
		$(SRC_DIR)Commands/ModeCommand.cpp \
		$(SRC_DIR)Commands/TopicCommand.cpp \
		$(SRC_DIR)Commands/PartCommand.cpp \
		$(SRC_DIR)Commands/InviteCommand.cpp \
		$(SRC_DIR)Commands/KickCommand.cpp

OBJS = $(SRCS:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)

BONUS_NAME = bot
BONUS_DIR = bonus/
BONUS_SRCS = $(BONUS_DIR)main.cpp \
				$(BONUS_DIR)Bot.cpp

BONUS_OBJ = $(BONUS_SRCS:$(BONUS_DIR)%.cpp=$(OBJ_DIR)bonus/%.o)

all: $(NAME)

bonus: all $(BONUS_NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -I $(INC_DIR) -o $(NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	$(CPP) $(CPPFLAGS) $(BONUS_OBJ) -I $(INC_DIR) -o $(BONUS_NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) -I $(INC_DIR) $< -c -o $@

$(OBJ_DIR)bonus/%.o: $(BONUS_DIR)%.cpp
	@mkdir -p $(dir $@)
	$(CPP) $(CPPFLAGS) -I $(INC_DIR) $< -c -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)

re: fclean all

.PHONY: all bonus fclean clean re