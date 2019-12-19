/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:03:14 by jmakela           #+#    #+#             */
/*   Updated: 2019/12/19 12:03:16 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"

/*
** Linked list struct.
** Each member of the list has two dimensional string,
** char c, which is char tetrimino is made of and next.
*/

typedef struct		s_list
{
	int				x;
	int				y;
	char			c;
	char			**data;
	struct s_list	*next;
}					t_list;

/*
** Struct that is used to validate the tetriminoes.
** It holds the amount of dots, hashtags, newlines,
** touching sides and count of pieces tetriminoes are made of.
*/

typedef struct		s_valid
{
	int				dot;
	int				hash;
	int				newl;
	int				sides;
	int				ret;
	int				count;
}					t_valid;

/*
** Solving functions use these as coordinates for the field.
*/

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

/*
** Just helping to make add_piece shorter
*/

typedef struct		s_points
{
	int				sx;
	int				sy;
	int				mapx;
	int				mapy;
	int				px;
	int				py;
}					t_points;

/*
** Validate.c
** Makes sure the input is correct.
*/

int					validate_input(char **argv);

/*
** List.c
** Used to create linked list.
*/

int					save_list(t_list **tmins, char **argv);

/*
** Solver.c
** Functions used in recursive backtracking.
*/

void				solver(t_list *tmins, char ***field, int size);

/*
** Adders.c
** Add_point moves the position of chosen field(field, tetrimino).
** Find_empty_point looks for the next possible position for tetrimino.
*/

int					find_empty_point(char ***field,
									t_point *point, int field_size);
int					add_point(t_point *point, int field_size);

/*
** Map_op.c
** Functions for creating, freeing and printing the field.
*/

void				print_field(char ***field);
int					make_field(char ***field, int field_size, int pieces);

/*
** Extras
*/

void				put_usage_message();

#endif
