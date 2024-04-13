# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 01:42:22 by dehamad           #+#    #+#              #
#    Updated: 2024/04/13 13:28:25 by dehamad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Delete the removing of .o files in the make rule 

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a
LIBS = -lreadline
MAIN = main.c delete_me_print_utils.c
PARSING = parsing.c lexer.c data_utils.c env_utils.c history_utils.c token_utils.c
EXECUTION = execution.c
BUILTINS = builtins.c cd.c echo.c env.c exit.c export.c pwd.c unset.c utils.c

SRCS = \
	$(addprefix src/, $(MAIN)) \
	$(addprefix src/parsing/, $(PARSING)) \
	$(addprefix src/execution/, $(EXECUTION)) \
	$(addprefix src/execution/builtins/, $(BUILTINS)) \
	
OBJS = $(SRCS:.c=.o) 

all: $(NAME)
	@$(MAKE) clean
bonus: $(BONUS_NAME)
sanitize: CFLAGS += -g3 -fsanitize=address
sanitize: re
valgrind:  valgrind --check-fds=true --leak-check=full -s --show-leak-kinds=all --track-origins=yes 

$(LIBFT):
	make -C libft
	
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME) 
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
