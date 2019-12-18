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
** The function takes as a parameter the field and the field size. It allocates
** space for the new field and writes it as empty and frees the old field. In the
** end the given pointer will point to the new field. If the size of the field is
** 2, the function creates the first field.  Function returns the size of the field.
*/
int		make_field(char ***field, int field_size)
{
	int		i;
	char	**temp_field;

	if (field_size == 2)
	{
		*field = (char**)malloc(sizeof(char*) * 3);
		field[0][0] = strdup("...\n");
		field[0][1] = strdup("...\n");
		field[0][2] = NULL;
		return(2);
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
	return (field_size);
}

/*
** The function takes as a parameter the field, the starting point in a struct
** that contains the x and y coordinates, and the field size. It writes the next
** empty point to pointed point pointer (that is a real sentence!) and return TRUE (1)
** or FALSE (0) if there is no more empty points on the field.
*/
int		find_empty_point(char ***field, t_point *point, int field_size)
{
	while(field[0][point->x][point->y] != '.')
	{
		if (point->y == field_size)
		{
			if (point->x == field_size)
				return(FALSE);
			else 
			{
				point->x++;
				point->y = 0;
			}
		}
		else
			point->y++;
	}
	return(TRUE);
}

/*
** Function takes as a parameter the struct point (containing the x and y
** coordinater), and field size. It returns TRUE (1) if it is able to add
** to the point, and FALSE (0) if adding would make it go outside the field.
** The point is given as a pointer, and the function writes the neede info on
** the struct pointed.
*/
int		add_point(t_point *point, int field_size)
{
	if (point->x == field_size - 1)
	{
		if (point->y == field_size - 1)
			return(FALSE);
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

/*
** Function takes as a parameter the field, the block that needs to be
** removed and the field size. It returns TRUE (1) on succesful removal
** The function goes through the block until it finds the ascii character
** used to mark the block. It then goes through the field and chances all
** blocks with that character to '.'.
*/
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
	while (add_point(&point, field_size))
	{
		if (field[0][point.y][point.x] == c)
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
int		set_piece(char ***field,t_point point,t_list *tmins,int field_size)
{
	t_point	piece;
	t_point	map;
	t_point start;
	int		blocks;
	int		i;

	i = 0;
	start.y = 0;
	start.x = 0;
	piece.y = 0;
	piece.x = 0;
	map.y = point.y;
	map.x = point.x;
	blocks = 0;
	ft_putendl("set piece 1");
	while (tmins->data[start.y][start.x] == '.')
		add_point(&start, 4);
	ft_putendl("set piece 2");
	while (map.y < field_size)
	{
		while (tmins->data[piece.y][piece.x] == '.')
			add_point(&piece, 4);
		ft_putendl("set piece 3");
		while (tmins->data[piece.y][piece.x] != '.')
		{
			ft_putendl("set piece 4");
			ft_putendl("set piece 5");
				ft_putnbr(map.x);
				ft_putstr(", ");
				ft_putnbr(piece.x);
				ft_putstr(", ");
				ft_putnbr(start.x);
				ft_putstr("\n");
			if (map.x < (piece.x - start.x) || field[0][map.y][map.x + piece.x - start.x] != '.')
			{
					while (field[0][i] != NULL)
					{
						ft_putstr(field[0][i]);
						i++;
					}
				remove_piece(field, tmins, field_size);
				return (FALSE);
			}
			ft_putendl("set piece 6");
			field[0][map.y][map.x + piece.x - start.x] = tmins->data[piece.x][piece.y];
			ft_putendl("set piece 7");
			blocks++;
			add_point(&piece, 4);
			map.y++;
			map.x = 0;

		}
	}
	if (blocks != 4)
	{
		remove_piece(field, tmins, field_size);
		return (FALSE);
	}
	while (field[0][i] != NULL)
	{
		ft_putstr(field[0][i]);
		i++;
	}
	return (TRUE);
}

/*
** THE RECURSIVE SOLVER! *drum roll*
** Takes as a parameter the field, list of blocks (tmins), size of the field
** (the number of blocks on one side of the square) and a point that contains
** values for x and y on the field (set to 0, 0 when first called)
** First, finds and empty point where no block has been set. Then tries to set
** the next block to it. If this fails, finds the next empty point. If there is 
** no next empty point, returns false (meaning the field could not be solved this
** way). If all the blocks has been set (tmins-> next == NULL), returns true,
** meaning the rigth answer has been found. When the piece has has been set, calls
** on itself with the next piece. If this operation returns true, the function 
** continues to return true. In other cases removes the piece set and goes to the
** next point. Continues then at the beginning of while.
*/
int		recursive_solver(char ***field, t_list *tmins, int field_size, t_point point)
{
	int		returnable;
	int		i;

	i = 0;
	while (find_empty_point(field, &point, field_size))
	{	
		ft_putendl("recursive_solver 1");
		while(!(set_piece(field, point, tmins, field_size)))
		{
			ft_putendl("recursive_solver 2");
			if (!(add_point(&point, field_size)) || !(find_empty_point(field, &point , field_size)))
				return (FALSE);
		}
		while (field[0][i] != NULL)
			{
				ft_putstr(field[0][i]);
				i++;
			}
		ft_putendl("recursive_solver 3");
		if (tmins->next == NULL)
			return (TRUE);
		ft_putendl("recursive_solver 4");
		returnable = recursive_solver(field, tmins->next, field_size, point);
		ft_putendl("recursive_solver 5");
		if(returnable == TRUE)
			return(TRUE);
		else
		{
			ft_putendl("recursive_solver 6");
			remove_piece(field, tmins, field_size);
			if (!(add_point(&point, field_size)))
				return (FALSE);
		}
	}
	return (FALSE);
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

	point.x = 0;
	point.y = 0;
	field_size = 2;
	field_size = make_field(field, field_size);
	if (!(recursive_solver(field, tmins, field_size, point)))
	{
		ft_putendl("solver2");
		field_size = make_field(field, (field_size + 1));
	}
	ft_putendl("solver3");
	return (field_size);
}