#include "fillit.h"

/*
** Shows the usage of fillit.
*/

void	put_usage_message()
{
	ft_putendl("Usage: fillit input_file");
	ft_putendl("    Input_file: File containing tetrimino pieces. Input file should follow these rules:");
	ft_putendl("    Each tetrimino is precisely 4 lines of 4 characters, each followed by a new line");
	ft_putendl("    Each character must be either a block character('#') or an empty character ('.')");
	ft_putendl("    Your file should contain between 1 and 26 Tetriminos.");
}

/*
** Main, where we do the error checking for invalid amount of arguments.
** If argument count is invalid, we put usage message. Else, we send the
** argument for validation. Wrong files, wrong format, wrong tetriminoes etc.
** result in "invalid input". If everything is OK, save_list gets the file
** and uses it to count the pieces and make a linked list where pieces are
** saved. Next the list is sent to the solver, which creates the map and
** does the actual solving of the puzzle. Finally we print the solution.
*/

int		main(int argc, char **argv)
{
	t_list			*tmins;
	int 			pieces;
	char			**field;

	tmins = NULL;
	if (argc != 2)
	{
		put_usage_message();
		return (0);
	}
	if (!(validate_input(argv)))
	{
		write(1, "invalid input", 13);
		return (0);
	}
	pieces = save_list(&tmins, argv);
	solver(tmins, &field, pieces);
	print_field(&field);
	return (0);
}
