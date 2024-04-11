# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dehamad <dehamad@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/09 01:42:22 by dehamad           #+#    #+#              #
#    Updated: 2024/04/11 19:55:56 by dehamad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
BONUS_NAME = bns

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft.a
LIBS = -lreadline
MAIN = main.c utils.c
PARSING = env_utils.c history_utils.c

# EXECUATION = execuation.c 

# MANDATORY_OBJS = $(MANDATORY:.c=.o)
# BONUS_OBJS = $(BONUS:.c=.o)

SRCS = \
	$(addprefix src/, $(MAIN)) \
	$(addprefix src/parsing/, $(PARSING)) \
	# $(addprefix src/execuation/, $(EXECUATION)) \

	
OBJS = $(SRCS:.c=.o) 

all: $(NAME)
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
