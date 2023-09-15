# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ckannane <ckannane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/04 18:48:43 by ckannane          #+#    #+#              #
#    Updated: 2023/08/30 15:51:25 by ckannane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	ft_memcpy.c ft_strlcpy.c ft_memmove.c\
		ft_atoi.c ft_memset.c ft_strlen.c \
		ft_bzero.c ft_putchar_fd.c ft_strmapi.c \
		ft_calloc.c ft_putendl_fd.c ft_strncmp.c \
		ft_putnbr_fd.c ft_strnstr.c \
		ft_isalnum.c ft_putstr_fd.c ft_strrchr.c \
		ft_isalpha.c ft_split.c ft_strtrim.c \
		ft_isascii.c ft_substr.c \
		ft_isdigit.c ft_strchr.c \
		ft_isprint.c ft_strdup.c ft_tolower.c \
		ft_itoa.c ft_striteri.c ft_toupper.c \
		ft_memchr.c ft_strjoin.c \
		ft_memcmp.c ft_strlcat.c \
		ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
		ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c \
		ft_lstadd_back.c\

OBJ = $(SRC:.c=.o)

CC = gcc

RM = rm -f

FLAGS = -Wall -Werror -Wextra

NAME = libft.a

all:		$(NAME)

$(NAME):	$(OBJ)
			ar rcs $(NAME) $(OBJ)

clean:
			$(RM) $(OBJ)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean $(NAME)