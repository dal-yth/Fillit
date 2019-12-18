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
** Mod_buf korvaa hashtagit oikeilla kirjaimilla ja palauttaa muokatun buffin.
*/

char *mod_buf(char *buf, char c)
{
	int i;
	/*
	char *new;

	new = (char *)malloc(sizeof(char) * 5);
	new = strcpy(new, buf);
	*/
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
** Kiitos Jaakko.
** Tässä luodaan uusi node, jonka char **data mallocoidaan,
** jotta jokaiselle saadaan oma erillinen muistipaikka,
** eikä pointteri yritä hakea aina samasta muistipaikasta arvoja.
*/

t_list *newnode(char **data)
{
	t_list *new;
	int i;

    i = 0;
    new = (t_list*)malloc(sizeof(t_list));
    new->data = (char**)malloc(sizeof(char*) * 5);
    while (i <= 3)
    {
        new->data[i] = (char*)malloc(sizeof(char) * 5);
        new->data[i] = data[i];
        i = i + 1;
    }
	new->data[i] = NULL;
	/*
	new = (t_list*)malloc(sizeof(t_list));
	new->data = (char**)malloc(sizeof(char*) * 5);
	new->data[0] = (char*)malloc(sizeof(char) * 5);
	new->data[1] = (char*)malloc(sizeof(char) * 5);
	new->data[2] = (char*)malloc(sizeof(char) * 5);
	new->data[3] = (char*)malloc(sizeof(char) * 5);
	new->data[0] = data[0];
	new->data[1] = data[1];
	new->data[2] = data[2];
	new->data[3] = data[3];
	*/
	new->next = NULL;
	return(new);
}

/*
** Lisää listan loppuun uuden noden, joka saa char **datan.
*/

void append(t_list **tetris, char **data)
{
	t_list *last;

	last = *tetris;
	if (*tetris == NULL)
	{
		*tetris = newnode(data);
		return;
	}
	while(last->next != NULL)
		last = last->next;
	last->next = newnode(data);
	return;
}

/*
** Sama funktio kuin save tetri, jota käytetään palojen tallentamiseen.
** Muokattu toimimaan linked listin kanssa.
*/

int save_list(t_list **tetris, char **argv)
{
	int fd;
	char *buf;
	char **piece;
	int i;
	int j;

	i = 0;
	j = 0;
	piece = (char**)malloc(sizeof(char*) * 5);
	fd = open(argv[1], O_RDONLY);
	while ((get_next_line(fd, &buf)) > 0)
	{
		buf = mod_buf(buf, 'A' + i);
		if (j <= 3)
			piece[j] = buf;
		if (j == 3)
			append(tetris, piece);
		j = j + 1;
		if (j == 5)
		{
			i = i + 1;
			j = 0;
		}
	}
	close(fd);
	free(piece);
	return(i + 1);
}
