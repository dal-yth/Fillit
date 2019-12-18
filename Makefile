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

INC = libft/includes/libft.h fillit.h

all: $(NAME)

$(NAME):
	gcc -c $(SRCS) -I $(INC)
	gcc -o $(NAME) $(OBJ) -L libft/ -lft

plain:
	clang -I libft/includes -o fillit.o -c fillit.c
	clang -I libft/includes -o solver.o -c solver.c
	clang -I libft/includes -o validate.o -c validate.c
	clang -I libft/includes -o main.o -c main.c
	clang -o $(NAME) main.o $(OBJ) -I libft/includes -L libft/ -lft

debug:
	gcc -c $(SRCS) -I $(INC) -g
	gcc -o $(NAME) $(OBJ) -g -L libft/ -lft

clean:
	rm -rf $(OBJ)
	rm -rf *~

fclean: clean
	rm -rf $(NAME)

re: fclean all
