# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ksnow-be <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/09 09:09:09 by ksnow-be          #+#    #+#              #
#    Updated: 2019/02/02 19:20:40 by sbruen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
TEST = ft_printf.out
SRCS = ft_putnbr.c printer.c ft_printf.c

OBJS = $(SRCS:.c=.o)

all: $(NAME) 

$(NAME):
	@gcc -c -Wall -Werror -Wextra libft/*.c -I libft/libft.h
	@gcc -c $(SRCS)
	@ar rc $(NAME) *.o

test:
	@gcc -g -L. -lftprintf $(SRCS) main.c -o $(TEST)
 
clean:
	@rm -rf *.o libft/*.o

fclean: clean
	@rm -rf $(NAME) libft/libft.a
re: fclean all
