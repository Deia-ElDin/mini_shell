# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: melshafi <melshafi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/25 03:20:29 by dehamad           #+#    #+#              #
#    Updated: 2024/06/25 18:56:41 by melshafi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar

GET_SRC = ft_get_next_line.c
IS_X_SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	ft_isprint.c ft_issep.c ft_isspace.c ft_issign.c ft_isdifferent_sign.c \
	ft_isempty_str.c ft_ispipe.c ft_isredirect.c ft_isdoubles.c ft_isquote.c
LEN_SRC = ft_intlen.c ft_strlen.c ft_ptrlen.c ft_uintlen_base.c
LST_SRC = ft_envnew.c ft_envadd_front.c ft_envsize.c ft_envlast.c \
	ft_envadd_back.c ft_envdelone.c ft_envclear.c ft_enviter.c \
	ft_envmap.c
MAL_SRC = ft_calloc.c ft_free.c ft_bzero.c
MATH_SRC = ft_abs.c
MEM_SRC = ft_memset.c ft_memcpy.c ft_memmove.c ft_memchr.c \
	ft_memcmp.c
NUM_SRC = ft_atoi.c ft_itoa.c
PRINT_SRC = ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_putlchar_fd.c ft_putlstr_fd.c ft_putptr_base_fd.c \
	ft_putnbr_base_fd.c ft_printf.c ft_pfchar.c ft_pfstr.c ft_pfptr.c \
	ft_pfint.c ft_pfuint.c ft_pfarr.c ft_pfutils.c
STR_SRC = ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
	ft_strncmp.c ft_strnstr.c ft_strdup.c ft_substr.c \
	ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c \
	ft_striteri.c ft_strcmp.c ft_strnjoin.c ft_strcdup.c ft_strndup.c
TO_X_SRC = ft_tolower.c ft_toupper.c ft_toint.c
LST_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
    ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
    ft_lstmap.c

SRCS = \
	$(addprefix get/, $(GET_SRC)) \
	$(addprefix is_x/, $(IS_X_SRC)) \
	$(addprefix len/, $(LEN_SRC)) \
	$(addprefix lst/, $(ENV_SRC)) \
	$(addprefix mal/, $(MAL_SRC)) \
	$(addprefix math/, $(MATH_SRC)) \
	$(addprefix mem/, $(MEM_SRC)) \
	$(addprefix num/, $(NUM_SRC)) \
	$(addprefix print/, $(PRINT_SRC)) \
	$(addprefix str/, $(STR_SRC)) \
	$(addprefix to_x/, $(TO_X_SRC)) \
	$(addprefix lst/, $(LST_SRC)) \

OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) -rcs $@ $^

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
