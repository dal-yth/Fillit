/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 12:48:27 by jmakela           #+#    #+#             */
/*   Updated: 2019/12/05 12:48:27 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Mod_buf finds hashtags in the string buf and changes them to
** char c, which is something between A-Z depending on which
** tetrimino we are currently saving to the list.
*/

static char		*mod_buf(char *buf, char c)
{
	int	i;

	i = 0;
	while(buf[i])
	{
		if (buf[i] == '#')
			buf[i] = c;
		i = i + 1;
	}
	return(buf);
}

/*
** Finds which character the current tetrimino has and returns it.
** The char is then saved in newnode function to the new member of the list.
*/

static char		find_char(char **data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data[i])
	{
		while (data[i][j])
		{
			if (data[i][j] != '.')
				return (data[i][j]);
			j = j + 1;
		}
		j = 0;
		i = i + 1;
	}
	return (0);
}

/*
** Thank you Jaakko.
** Newnode takes two dimensional string as data and stores
** it to our list. New node and it's data is allocated each
** time, because without allocation, new->data always points to
** a memory location of char **data and when save_list function
** assigns different data to char **data, it changes data within
** the list as well.
*/

static t_list	*newnode(char **data)
{
	t_list	*new;
	int		i;

    i = 0;
    new = (t_list*)malloc(sizeof(t_list));
    new->data = (char**)malloc(sizeof(char*) * 5);
    while (i <= 3)
    {
        new->data[i] = data[i];
        i = i + 1;
    }
	new->data[i] = NULL;
	new->next = NULL;
	new->c = find_char(new->data);
	return (new);
}

/*
** Appends a new node at the end of the list.
** Gets the pointer to the head of the list and data to
** assign to the new node. We create temporary node last
** which becomes the new temporary head. We can then go through
** the list, until we find the last node, then we assign
** a new node to be the last node. Returns i + 1,
** which is used to count how many tetriminoes we have.
*/

static int		append(t_list **tmins, char **data, int i)
{
	t_list *last;

	last = *tmins;
	if (*tmins == NULL)
	{
		*tmins = newnode(data);
		return (i + 1);
	}
	while (last->next != NULL)
		last = last->next;
	last->next = newnode(data);
	return (i + 1);
}

/*
** Saves the tetriminos to a linked list.
** We use get_next_line to read argv data line by line.
** Mod_buf changes hashtags into chars A-Z.
** Those lines are saved to a two dimensional str piece.
** Piece is then saved as data to the list. Returns the
** amount of pieces saved to list.
*/

int				save_list(t_list **tmins, char **argv)
{
	int		fd;
	char	*buf;
	char	**piece;
	int		i;
	int		j;

	i = 0;
	j = 0;
	piece = (char**)malloc(sizeof(char*) * 6);
	fd = open(argv[1], O_RDONLY);
	while ((get_next_line(fd, &buf)) > 0)
	{
		buf = mod_buf(buf, 'A' + i);
		if (j <= 3)
			piece[j] = buf;
		if (j == 3)
			i = append(tmins, piece, i);
		j = j + 1;
		if (j == 5)
			j = 0;
	}
	close(fd);
	free(piece);
	return (i);
}
