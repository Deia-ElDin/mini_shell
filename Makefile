# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 01:42:22 by dehamad           #+#    #+#              #
#    Updated: 2024/06/20 19:29:24 by dehamad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Delete the removing of .o files in the make rule
# Delete the CFLAGS -g3 -fsanitize=address

NAME = minishell

# readline_header_path = -I /Users/dehamad/homebrew/opt/readline/include
# readline_lib_path = -L /Users/dehamad/homebrew/opt/readline/lib

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -g3 # $(readline_header_path)
# CFLAGS = -Wall -Wextra -Werror -Iincludes -g3 -fsanitize=address

LIBFT = includes/libft/libft.a
LIBS = -lreadline
# LIBS = $(readline_lib_path) -lreadline

MAIN = main.c delete_me.c

PARSING_UTILS_PARSING = parse_cmd.c parse_pipe.c parse_redir.c
EXECUTION = execution.c and_or_exec.c redirections.c simple_cmd.c pipe_cmd.c utils.c
EXECUTION_UTILS = env_utils.c cmd_utils.c str_join.c pipe_utils.c here_doc.c redir_utils.c
EXECUTION_BUILTINS = builtins.c cd.c echo.c env.c exit_shell.c export.c pwd.c
UTILS = error.c exit.c data.c
PARSING = lexer.c parser.c
PARSING_UTILS_ENV = env_add.c env_expansion.c env_free.c env_get.c env_last.c \
	env_lstclear.c  env_lstsize.c env_new.c env_set.c env_toarr.c env_tolst.c \
	env_concat.c env_unset.c
PARSING_UTILS_TOKEN = token_add.c token_delone.c token_lstclear.c token_merge.c \
	token_tolst.c token_validation.c token_last.c token_reorder.c
PARSING_UTILS_AST = ast_lstclear.c ast.c
UTILS = error.c data.c utils.c

SRCS = \
	$(addprefix src/, $(MAIN)) \
	$(addprefix src/parsing/, $(PARSING)) \
	$(addprefix src/parsing/utils/parsing/, $(PARSING_UTILS_PARSING)) \
	$(addprefix src/parsing/utils/env/, $(PARSING_UTILS_ENV)) \
	$(addprefix src/parsing/utils/tokens/, $(PARSING_UTILS_TOKEN)) \
	$(addprefix src/parsing/utils/ast/, $(PARSING_UTILS_AST)) \
	$(addprefix src/execution/, $(EXECUTION)) \
	$(addprefix src/execution/utils/, $(EXECUTION_UTILS)) \
	$(addprefix src/execution/builtins/, $(EXECUTION_BUILTINS)) \
	$(addprefix src/utils/, $(UTILS))

OBJS = $(SRCS:.c=.o)

all: $(NAME)
bonus: $(BONUS_NAME)
sanitize: CFLAGS += -fsanitize=address
sanitize: all
valgrind: all
	valgrind --trace-children=yes --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions="rules/valgrind.txt" -s ./minishell

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
