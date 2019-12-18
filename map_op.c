#include "fillit.h"

/*
** The function creates a new string of size num, and allocates it with
** value. The fresh string is returned.
*/

char	*ft_strset(char value, size_t num)
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
** Printer funktion for the field;
*/

void print_field(char ***field)
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
** New make_field 
*/

int		make_field(char ***field, int pieces, int grow)
{
	int		i;
	int		size;
	size = 2;
	i = 0;
	if(grow > 0)
	{
		while (field[0][i] != NULL)
		{
			free(field[0][i]);
			i++;	
		}
		free(field);
	}
	while (size * size < (pieces * 4))
		size = size + 1;
	size = size + grow;
	*field = (char**)malloc(sizeof(char*) * (size + 1));
	i = 0;
	while(i < size)
	{
		field[0][i] = ft_strset('.', size);
		i = i + 1;
	}
	field[0][i] = NULL;
	return(size);
}

