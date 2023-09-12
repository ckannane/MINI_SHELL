# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 21:18:58 by ckannane          #+#    #+#              #
#    Updated: 2023/09/12 16:34:30 by ckannane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRC = pars/run.c pars/tools.c execc/ft_echo.c execc/ft_pwd.c execc/ft_cd.c execc/ft_export.c execc/ft_ls.c execc/env.c execc/unset.c execc/rederection.c

OBJ = $(SRC:.c=.o)

NAME = minishell

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) -L/goinfre/ckannane/homebrew/opt/readline/lib $(CFLAGS) $(OBJ) Libft/libft.a -lreadline -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all