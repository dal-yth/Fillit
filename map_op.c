#include "fillit.h"

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
	write(1, "\n", 1);
}

/*
** New make_field 
*/

int		make_field(char ***field, int pieces, int grow)
{
	int		i;

	i= 0;
	if(grow > 0)
	{
		while (field[0][i] != NULL)
		{
			free(field[0][i]);
			i++;	
		}
	}
	i = pieces * 4;
	pieces = 2;
	while (pieces * pieces < i)
		pieces = pieces + 1;
	pieces = pieces + grow;
	*field = (char**)malloc(sizeof(char*) * (pieces + 1));
	i = 0;
	while(i < pieces)
	{
		field[0][i] = ft_strset('.', pieces);
		i = i + 1;
	}
	field[0][i] = NULL;
	print_field(field);
	return(pieces);
}