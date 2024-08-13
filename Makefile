# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mamerlin <mamerlin@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 19:33:09 by hakaraka          #+#    #+#              #
#    Updated: 2024/08/13 16:58:40 by mamerlin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Check if readline library is installed on Linux or Mac, if not show message
CURRENT_OS = $(uname -s)
ifeq ($(CURRENT_OS), Linux)
check_readline:
	@test -f /usr/include/readline/readline.h || { echo "Readline library \
		not found. Please install it using the following command:"; \
		echo "sudo apt-get install make libreadline-dev"; \
		exit 1; }
else ifeq ($(CURRENT_OS), Darwin)
	READLINE_DIR := $(shell if [ -d ~/.brew/opt/readline ]; then \
		echo ~/.brew/opt/readline; \
		else if [ -d /usr/local/opt/readline ]; \
		then echo /usr/local/opt/readline; \
		else echo "Readline library not found. Please install it via"; \
			echo "brew install readline"; \
			exit 1; \
		fi; fi)
	INCS = -I $(READLINE_DIR)/include
	LIBS = -L $(READLINE_DIR)/lib
endif

NAME 		= minishell
CFLAGS 		= -Wall -Wextra -Werror
CC 			= cc
SRC_DIR 	= src
OBJ_DIR 	= obj
LIBFT_DIR 	= libft
LIBFT 		= libft/libft.a
RM 			= rm -rf

SRC = main.c tokenizer.c utils_token.c parser.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	@echo "Compiling minishell..."
	@$(CC) $(INCS) $(LIBS)  $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $@
	@echo "Done!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c  $< -o $@

$(LIBFT):
	@echo "Compiling libft..."
	@make bonus -C libft
	@make -C libft

clean:
	@echo "Cleaning..."
	@make clean -C libft
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "Fcleaning..."
	$(RM) $(NAME)
	$(RM) $(LIBFT)

git:
	git add .
	git commit -m "update"
	git push

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

re: fclean
	@make all

.PHONY: all clean fclean re
