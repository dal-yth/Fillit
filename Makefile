# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmakela <jmakela@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 10:44:33 by jmakela           #+#    #+#              #
#    Updated: 2019/12/18 16:21:01 by jmakela          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

SRCS = list.c solver.c validate.c main.c map_op.c adders.c

OBJ = $(SRCS:.c=.o)

INC = fillit.h

all: $(NAME)

$(NAME):
	cd libft && make re
	gcc -c -Wall -Wextra -Werror $(SRCS) -I $(INC)
	gcc -Wall -Wextra -Werror -o $(NAME) $(OBJ) libft/libft.a

clean:
	rm -rf $(OBJ)
	rm -rf *~

fclean: clean
	rm -rf $(NAME)

re: fclean all
