/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 17:54:58 by hlaineka          #+#    #+#             */
/*   Updated: 2019/12/18 17:55:00 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** The function takes as a parameter the field, the starting point in a struct
** that contains the x and y coordinates, and the field size. It writes the next
** empty point to pointed point pointer (that is a real sentence!) and
** return TRUE (1) or FALSE (0) if there is no more empty points on the field.
*/

int		find_empty_point(char ***field, t_point *point, int field_size)
{
	while (field[0][point->y][point->x] != '.')
	{
		if (point->x == field_size - 1)
		{
			if (point->y == field_size - 1)
				return (FALSE);
			else 
			{
				point->y++;
				point->x = 0;
			}
		}
		else
			point->x++;
	}
	return (TRUE);
}

/*
** Function takes as a parameter the struct point (containing the x and y
** coordinates), and field size. It returns TRUE (1) if it is able to add
** to the point, and FALSE (0) if adding would make it go outside the field.
** The point is given as a pointer, and the function writes the needed info on
** the struct pointed.
*/

int		add_point(t_point *point, int field_size)
{
	if (point->x == field_size - 1)
	{
		if (point->y == field_size - 1)
			return (FALSE);
		else 
		{
			point->y++;
			point->x = 0;
		}
	}
	else
		point->x++;
	return (TRUE);
}
