# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 01:42:22 by dehamad           #+#    #+#              #
#    Updated: 2024/04/21 19:02:25 by dehamad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Delete the removing of .o files in the make rule 
# Delete the CFLAGS -g3 -fsanitize=address

NAME = minishell

CC = cc
# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -Wall -Wextra -Werror -g3

LIBFT = includes/libft/libft.a
LIBS = -lreadline

MAIN = main.c delete_me.c
PARSING = lexer.c parser.c 
PARSING_UTILS = ast.c
PARSING_UTILS_ENV = env_add.c env_clear.c env_get.c env_last.c env_new.c \
	env_size.c env_toarr.c env_tolst.c env_update.c env_expansion.c
PARSING_UTILS_TOKEN = token_add.c token_clear.c token_new.c token_tolst.c \
	token_type.c token_validation.c
EXECUTION = execution.c
EXECUTION_BUILTINS = builtins.c cd.c echo.c env.c exit.c export.c pwd.c unset.c
UTILS = init.c free.c exit.c error.c

SRCS = \
	$(addprefix src/, $(MAIN)) \
	$(addprefix src/parsing/, $(PARSING)) \
	$(addprefix src/parsing/utils/, $(PARSING_UTILS)) \
	$(addprefix src/parsing/utils/env/, $(PARSING_UTILS_ENV)) \
	$(addprefix src/parsing/utils/tokens/, $(PARSING_UTILS_TOKEN)) \
	$(addprefix src/execution/, $(EXECUTION)) \
	$(addprefix src/execution/builtins/, $(EXECUTION_BUILTINS)) \
	$(addprefix src/utils/, $(UTILS))
	
OBJS = $(SRCS:.c=.o) 

all: $(NAME)
bonus: $(BONUS_NAME)
sanitize: CFLAGS += -g3 -fsanitize=address
sanitize: re
valgrind: re
	valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions="rules/valgrind.txt" -s ./$(NAME)

$(LIBFT):
	make -C ./includes/libft

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJS)
	make -C ./includes/libft clean

fclean: clean
	rm -f $(NAME) 
	make -C ./includes/libft fclean

re: fclean all

.PHONY: all clean fclean re
