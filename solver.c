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
** The function takes as a parameter the field, the starting point in a struct
** that contains the x and y coordinates, and the field size. It writes the next
** empty point to pointed point pointer (that is a real sentence!) and return TRUE (1)
** or FALSE (0) if there is no more empty points on the field.
*/

int		find_empty_point(char ***field, t_point *point, int field_size)
{
	while(field[0][point->y][point->x] != '.')
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

int		set_piece(char ***field,t_list *tmins,int field_size, t_point *point)
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

int		recursive_solver(char ***field, t_list *tmins, int field_size)
{
	t_point point;

	point.x = 0;
	point.y = 0;
	if (tmins == NULL)
		return (TRUE);
	while (find_empty_point(field, &point, field_size))
	{	
		while(!(set_piece(field, tmins, field_size, &point)))
		{
			if (!(add_point(&point, field_size)) || !(find_empty_point(field, &point, field_size)))
				return (FALSE);
		}
		print_field(field);
		if(!(recursive_solver(field, tmins->next, field_size)))
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
** First makes a 3x3 field, and uses recursive solver to solve it.
** if recursive solver fails, makes the field one bigger, and does 
** this in a loop until the solution is found. Writes the new field
** straight in to the parameter and returns the size of the field
*/

int		solver(t_list *tmins, char ***field, int pieces)
{
	int		grow;

	grow = 0;
	pieces = make_field(field, pieces, grow);
	print_field(field);
	while (!(recursive_solver(field, tmins, pieces)))
	{
		grow = grow + 1;
		pieces = make_field(field, pieces, grow);
	}
	return (pieces);
}