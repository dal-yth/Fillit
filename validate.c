/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <jmakela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 16:49:03 by jmakela           #+#    #+#             */
/*   Updated: 2019/12/18 17:36:35 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Initializes t_valid struct ok to zero values.
*/

void	init_struct(t_valid *ok)
{
	ok->dot = 0;
	ok->hash = 0;
	ok->newl = 0;
	ok->sides = 0;
}

/*
** Function that validates the tetrimino piece.
** From 0 to 18 is 19 chars, which is everything we have to check.
** Finds a hashtag and checks if it has other neighbouring hashtags.
** Counts the connecting sides of each hashtag, correct hashtags
** have 6 or 8(square) connected sides. Otherwise, tetrimino is
** false and 0 is returned.
*/

int		validate_tetri(char *buf, t_valid *ok)
{
	int i;

	i = 0;
	while (i <= 18)
	{
		if (buf[i] == '#')
		{
			if (buf[i + 1] == '#' && (i + 1) <= 18)
				ok->sides = ok->sides + 1;
			if (buf[i - 1] == '#' && i != 0)
				ok->sides = ok->sides + 1;
			if (buf[i + 5] == '#' && (i + 5) <= 18)
				ok->sides = ok->sides + 1;
			if (buf[i - 5] == '#' && (i - 5) >= 0)
				ok->sides = ok->sides + 1;
		}
		i = i + 1;
	}
	if (ok->sides == 6 || ok->sides == 8)
		return (1);
	return (0);
}

/*
** Helper function that checks for characters in buf, position i.
** If something else than '.', '#' or '\n' is found, returns 0.
** Otherwise, counts the amount of dots, hashtags and newlines,
** if they are in the correct position as determined by ok->count.
*/

int		buf_helper(char *buf, t_valid *ok, int i)
{
	if (buf[i] != '.' && buf[i] != '#' && buf[i] != '\n')
		return (0);
	if (buf[i] == '.' && ok->count <= 4)
		ok->dot = ok->dot + 1;
	if (buf[i] == '#' && ok->count <= 4)
		ok->hash = ok->hash + 1;
	if (buf[i] == '\n' && ((i + 1) % 5 == 0 || i == 20))
	{
		ok->newl = ok->newl + 1;
		ok->count = 0;
	}
	return (1);
}

/*
** Checks the buf string and attempts to find correct amount of dots,
** hashtags and newlines. Actual counting of dots, hashtags and newlines
** is done by helper function buf_helper. At the end there are two different
** checks because the last read has only 20 characters, instead of the usual
** 21 chars, when we read a tetrimino. This is because between two tetriminos
** there is an extra newline, that is not found after the last piece.
*/

int		check_buf(char *buf, t_valid *ok, int ret)
{
	int i;

	i = 0;
	ok->count = 1;
	if (!buf)
		return (0);
	while (buf[i])
	{
		if (!(buf_helper(buf, ok, i)))
			return (0);
		i = i + 1;
		ok->count = ok->count + 1;
	}
	if (ret == 20)
	{
		if (!(ok->dot == 12 && ok->hash == 4 && ok->newl == 4))
			return (0);
		return (1);
	}
	if (!(ok->dot == 12 && ok->hash == 4 && ok->newl == 5))
		return (0);
	return (1);
}

/*
** Validate_input function that does the reading of argv and
** calls other checking and validating functions to verify
** tetriminos. BUFF_SIZE is 21, so we can always read single
** tetrimino and the newline after. Each cycle, we call
** initialize our ok struct, call for check_buf and validate_tetri
** and count the piece. Finally we free our struct and check if
** the last reading was correct.
*/

int		validate_input(char **argv)
{
	int		fd;
	int		tcount;
	int		ret;
	char	buf[BUFF_SIZE + 1];
	t_valid	*ok;

	tcount = 0;
	ok = (t_valid*)malloc(sizeof(t_valid));
	fd = open(argv[1], O_RDONLY);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		init_struct(ok);
		ok->ret = ret;
		buf[ret] = '\0';
		if (!(check_buf(buf, ok, ret)) || !(validate_tetri(buf, ok)))
			return (0);
		tcount = tcount + 1;
		if (tcount > 26)
			return (0);
	}
	close(fd);
	if (ok->ret != 20)
		return (0);
	free(ok);
	return (1);
}
