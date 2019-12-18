/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:54:06 by hlaineka          #+#    #+#             */
/*   Updated: 2019/12/18 17:54:09 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Function takes as a parameter the field, the block that needs to be
** removed and the field size. It returns TRUE (1) on succesful removal.
** It then goes through the field and chances all blocks with matching
** tmins->c character to dots.
*/
static int	remove_piece(char ***field, t_list *tmins, int field_size)
{
	t_point	point;

	point.x = 0;
	point.y = 0;
	if (field[0][point.y][point.x] == tmins->c)
		field[0][point.y][point.x] = '.';
	while (add_point(&point, field_size))
	{
		if (field[0][point.y][point.x] == tmins->c)
			field[0][point.y][point.x] = '.';
	}
	return (TRUE);
}

/*
** Takes as a parameter the field, point where the piece is to be set, the piece
** to be set and the field size. Return an integer with value TRUE (1) if it was
** able to set the piece, and FALSE (0), if it could not set the piece
** First the function goes through the piece to find the first block cell. This
** point is saved in struct start, which contains the x and y coordinates. Then
** the function goes through the rest of the cells of the piece and sets every
** block cell to the field. If the function tries to write outside field or has
** added some other amount of block cells than 4, it will remove the ones it has
** added and return FALSE.
*/

static int	set_piece(char ***field, t_list *tmins, int field_size, t_point *point)
{
	t_point	piece;
	t_point	map;
	t_point start;
	int		blocks;

	start.y = 0;
	start.x = 0;
	piece.y = 0;
	piece.x = 0;
	map.y = point->y;
	map.x = point->x;
	blocks = 0;
	while (tmins->data[start.y][start.x] == '.')
		add_point(&start, 4);
	while (map.y < field_size)
	{
		while (tmins->data[piece.y][piece.x] == '.')
		{
			if (!(add_point(&piece, 4)))
				break;
		}
		while (tmins->data[piece.y][piece.x] != '.' && blocks < 4)
		{
			if ((map.x + piece.x - start.x) < 0 || (map.x + piece.x - start.x) >= field_size || field[0][map.y][map.x + piece.x - start.x] != '.')
			{
				remove_piece(field, tmins, field_size);
				return (FALSE);
			}
			field[0][map.y][map.x + piece.x - start.x] = tmins->data[piece.y][piece.x];
			add_point(&piece, 4);
			blocks++;
		}
		map.y++;
		map.x = point->x;
	}
	if (blocks != 4)
	{
		remove_piece(field, tmins, field_size);
		return (FALSE);
	}
	return (TRUE);
}

/*
** THE RECURSIVE SOLVER! *drum roll*
** Takes as a parameter the field, list of blocks (tmins), size of the field
** (the number of blocks on one side of the square) and a point that contains
** values for x and y on the field (set to 0, 0 when first called).
** First, finds and empty point where no block has been set. Then tries to set
** the next block to it. If this fails, finds the next empty point. If there is
** no next empty point, returns false (meaning the field could not be solved this
** way). If all the blocks has been set (tmins == NULL), returns true,
** meaning the right answer has been found. When the piece has has been set, calls
** on itself with the next piece. If this operation returns true, the function
** continues to return true. In other cases removes the piece set and goes to the
** next point. Continues then at the beginning of while loop.
*/

static int	recursive_solver(char ***field, t_list *tmins, int field_size)
{
	t_point point;

	point.x = 0;
	point.y = 0;
	if (tmins == NULL)
		return (TRUE);
	while (find_empty_point(field, &point, field_size))
	{	
		while (!(set_piece(field, tmins, field_size, &point)))
		{
			if (!(add_point(&point, field_size)) || !(find_empty_point(field, &point, field_size)))
				return (FALSE);
		}
		if (!(recursive_solver(field, tmins->next, field_size)))
		{
			remove_piece(field, tmins, field_size);
			if (!(add_point(&point, field_size)))
				return (FALSE);
		}
		else
			return (TRUE);
	}
	return (FALSE);
}

/*
** Makes smallest possible field that can fit all the pieces.
** Then attempts to solve the field, if recursive solver fails,
** makes the field one bigger, and does this in a loop until
** the solution is found.
*/

void		solver(t_list *tmins, char ***field, int pieces)
{
	int		grow;
	int		size;

	grow = 0;
	size = make_field(field, pieces, grow);
	while (!(recursive_solver(field, tmins, size)))
	{
		grow = grow + 1;
		size = make_field(field, pieces, grow);
	}
}
