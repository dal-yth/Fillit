#include "fillit.h"

/*
** The function creates a new string of size num, and allocates it with
** char value. The fresh string is then returned.
*/

static char	*ft_strset(char value, size_t num)
{
	unsigned int	i;
	char			*returnable;

	i = 0;
	if ((returnable = (char*)malloc(sizeof(char) * (num + 1))) != NULL)
	{
		while (i < num)
		{
			returnable[i] = value;
			i++;
		}
		returnable[i] = '\0';
	}
	return (returnable);
}

/*
** Printer function for the field.
** It prints the field. That's it.
*/

void		print_field(char ***field)
{
	int i;

	i = 0;
	while (field[0][i] != NULL)
	{
		ft_putstr(field[0][i]);
		write(1, "\n", 1);
		i++;
	}
}

/*
** Frees the allocated field field.
*/

static void	free_field(char ***field)
{
	int i;

	i = 0;
	while (field[0][i] != NULL)
	{
		free(field[0][i]);
		i++;
	}
	free(field[0]);
}

/*
** Function to make the field for tetriminos.
** Gets the pointer to a two dimensional string field,
** amount of tetriminoes and grow, which is used to make
** bigger fields if first one can't fit all tetriminoes.
** Check for grow if we have to free the old field, before
** creating a new field. Then checks based on piece count,
** how large field it should create and allocates memory
** for it. Ft_strset fills the field with dots.
*/

int			make_field(char ***field, int pieces, int grow)
{
	int		i;
	int		size;

	size = 2;
	i = 0;
	if (grow > 0)
		free_field(field);
	while (size * size < (pieces * 4))
		size = size + 1;
	size = size + grow;
	*field = (char**)malloc(sizeof(char*) * (size + 1));
	i = 0;
	while (i < size)
	{
		field[0][i] = ft_strset('.', size);
		i = i + 1;
	}
	field[0][i] = NULL;
	return (size);
}
