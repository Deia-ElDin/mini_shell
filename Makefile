# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 01:42:22 by dehamad           #+#    #+#              #
#    Updated: 2024/04/29 23:15:37 by dehamad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Delete the removing of .o files in the make rule 
# Delete the CFLAGS -g3 -fsanitize=address

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

LIBFT = includes/libft/libft.a
LIBS = -lreadline

MAIN = main.c delete_me.c


PARSING = lexer.c parser.c 
PARSING_UTILS_ENV = env_add.c  env_expansion.c env_get.c env_last.c env_lstclear.c \
	env_lstsize.c env_new.c env_toarr.c env_tolst.c env_update.c
PARSING_UTILS_TOKEN = token_add.c token_delone.c token_lstclear.c token_merge.c \
	token_tolst.c token_validation.c
PARSING_UTILS_AST = ast_add.c ast_head.c ast_new.c
	
PARSING_UTILS_ENV = env_add.c  env_expansion.c env_get.c env_last.c env_lstclear.c \
	env_lstsize.c env_new.c env_toarr.c env_tolst.c env_update.c
PARSING_UTILS_TOKEN = token_add.c token_delone.c token_lstclear.c token_merge.c \
	token_tolst.c token_validation.c token_last.c
PARSING_UTILS_AST = ast_lstclear.c
	
EXECUTION = execution.c
EXECUTION_BUILTINS = builtins.c cd.c echo.c env.c exit.c export.c pwd.c unset.c
UTILS = error.c exit.c data.c 

SRCS = \
	$(addprefix src/, $(MAIN)) \
	$(addprefix src/parsing/, $(PARSING)) \
	$(addprefix src/parsing/utils/env/, $(PARSING_UTILS_ENV)) \
	$(addprefix src/parsing/utils/tokens/, $(PARSING_UTILS_TOKEN)) \
	$(addprefix src/parsing/utils/ast/, $(PARSING_UTILS_AST)) \
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
