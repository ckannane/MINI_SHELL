# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 21:18:58 by ckannane          #+#    #+#              #
#    Updated: 2023/09/15 23:51:11 by ckannane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g


SRC =	pars/run.c pars/tools.c pars/tool_par.c \
		pars/tool2.c pars/tool3.c execc/ft_echo.c \
		execc/ft_pwd.c execc/ft_cd.c execc/ft_export.c \
		execc/env.c execc/unset.c \
		execc/rederection.c pars/handl_quote.c pars/set_com.c free.c

OBJ = $(SRC:.c=.o)

NAME = minishell

LDFLAGS = "-L/Users/ckannane/.brew/opt/readline/lib"

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) Libft/libft.a -lreadline -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all