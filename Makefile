# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 01:42:22 by dehamad           #+#    #+#              #
#    Updated: 2024/04/19 21:16:28 by dehamad          ###   ########.fr        #
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
PARSING = lexer.c parser.c validations.c
PARSING_UTILS = env.c token.c ast.c
EXECUTION = execution.c
EXECUTION_BUILTINS = builtins.c cd.c echo.c env.c exit.c export.c pwd.c unset.c
UTILS = init.c free.c exit.c error.c

SRCS = \
	$(addprefix src/, $(MAIN)) \
	$(addprefix src/parsing/, $(PARSING)) \
	$(addprefix src/parsing/utils/, $(PARSING_UTILS)) \
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
