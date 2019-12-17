#include "fillit.h"

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

int		make_field(char ***field, int field_size)
{
	int		i;
	char	**temp_field;

	if (field_size == 2)
	{
		*field = (char**)malloc(sizeof(char*) * 4);
		field[0][0] = strdup("...\n");
		field[0][1] = strdup("...\n");
		field[0][2] = strdup("...\n");
		field[0][3] = NULL;
		return(3);
	}
	else
	{
		temp_field = (char**)malloc(sizeof(char*) * field_size + 1);
		i = 0;
		while (field[0][i] != NULL)
		{
			temp_field[i] = ft_strjoin(ft_strset('.', field_size), "\n");
			free(field[0][i]);
			i++;	
		}
		free(*field);
		*field = temp_field;
		while (i < field_size)
		{
			field[0][i] = ft_strjoin(ft_strset('.', field_size), "\n");
			i++;
		}
		field[0][i] = NULL;
		return(i);
	}
	return (0);
}

int		find_empty_point(char ***field, t_point point, int field_size)
{
	while(field[0][point.x][point.y] != '.')
	{
		if (point.y == field_size)
		{
			if (point.x == field_size)
				return(FALSE);
			else 
			{
				point.x++;
				point.y = 0;
			}
		}
		else
			point.y++;
	}
	return(TRUE);
}

int		add_point(t_point point, int field_size)
{
	if (point.y == field_size)
	{
		if (point.x == field_size)
			return(FALSE);
		else 
		{
			point.x++;
			point.y = 0;
		}
	}
	else
		point.y++;
	return (TRUE);
}

int		remove_piece(char ***field, t_list *tmins, int field_size)
{
	int		i;
	int		w;
	char	c;
	t_point	point;

	i = 0;
	w = 0;
	point.x = 0;
	point.y = 0;
	while (w < 4)
	{
		while(i < 4)
		{
			if (tmins->data[w][i] != '.')
			{
				c = tmins->data[w][i];
				break;
			}
			i ++;
		}
		i = 0;
		w++;
	}
	if (field[0][point.y][point.x] == c)
		field[0][point.y][point.x] = '.';
	while (add_point(point, field_size))
	{
		if (field[0][point.y][point.x] == c)
			field[0][point.y][point.x] = '.';
	}
	return (TRUE);
}


int		set_piece(char ***field,t_point point,t_list *tmins,int field_size)
{
	int	i;
	int	w;
	int x;
	int	y;
	int j;

	x = point.x;
	y = point.y;
	i = 0;
	w = 0;
	j = 0;
	while (tmins->data[w][i] != '.')
		i++;
	j = -i;
	while (w < field_size)
	{
		while (tmins->data[w][i] != '.')
			i++;
		while (tmins->data[w][i] == '.')
		{
			if (field[0][y + w][x + i + j] != '.')
			{
				remove_piece(field, tmins, field_size);
				return (FALSE);
			}
			field[0][y + w][x + i + j] = tmins->data[w][i];
			i++;
		}
		i = 0;
		j = 0;
		w++;
	}
	return (TRUE);
}

/*
** THE RECURSIVE SOLVER! *drum roll*
** First, finds and empty point where no block has been set. Then tries to set
** the next block to it. If this fails, finds the next empty point. If there is 
** no next empty point, returns false (meaning the field could not be solved this
** way). If all the blocks has been set (tmins-> next == NULL), returns true,
** meaning the rigth answer has been found. When the piece has has been set, calls
** on itself with the next piece. If this operation returns true, the function 
** continues to return true. In other cases HETKINEN TÄMÄ TÄYTYY TEHDÄ WHILESSA VAI MITEN
*/
int		recursive_solver(char ***field, t_list *tmins, int field_size, t_point point)
{
	int		returnable;

	find_empty_point(field, point, field_size);
	while(!(set_piece(field, point, tmins, field_size)))
	{
		if (!(add_point(point, field_size)) || !(find_empty_point(field, point , field_size)))
			return (FALSE);
	}
	if (tmins->next == NULL)
		return (TRUE);
	returnable = recursive_solver(field, tmins->next, field_size, point);
	if(returnable == TRUE)
		return(TRUE);
	else
	{
		remove_piece(field, tmins, field_size);
		if (!(add_point(point, field_size)))
			return (FALSE);
		returnable = recursive_solver(field, tmins, field_size, point);
	}
	return (returnable);
}

/*
** First makes a 3x3 field, and uses recursive solver to solve it.
** if recursive solver fails, makes the field one bigger, and does 
** this in a loop until the solution is found. Writes the new field
** straight in to the parameter and returns the size of the field
*/
int		solver(t_list *tmins, char ***field)
{
	int		field_size;
	t_point point;

	ft_putendl("solver0");
	point.x = 0;
	point.y = 0;
	field_size = 2;
	ft_putendl("solver");
	field_size = make_field(field, field_size);
	ft_putendl("solver1");
	if (!(recursive_solver(field, tmins, field_size, point)))
	{
		ft_putendl("solver2");
		field_size = make_field(field, (field_size + 1));
	}
	ft_putendl("solver3");
	return (field_size);
}