/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <jmakela@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 11:55:03 by jmakela           #+#    #+#             */
/*   Updated: 2019/12/19 12:04:20 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Shows the usage of fillit.
*/

void	put_usage_message(void)
{
	ft_putendl("Usage: fillit input_file");
	ft_putendl("\tInput_file: File containing tetrimino pieces.");
	ft_putendl("\tInput file should follow these rules:");
	ft_putendl("\tTetrimino is 4 lines of 4 chars, each ends with newline.");
	ft_putendl("\tBetween two tetriminoes there must be a newline.");
	ft_putendl("\tEach char must be a block char('#') or an empty char('.')");
	ft_putendl("\tYour file should contain between 1 and 26 Tetriminos.");
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
	int				pieces;
	char			**field;

	tmins = NULL;
	if (argc != 2)
	{
		put_usage_message();
		return (0);
	}
	if (!(validate_input(argv)))
	{
		write(1, "error\n", 6);
		return (0);
	}
	pieces = save_list(&tmins, argv);
	solver(tmins, &field, pieces);
	print_field(&field);
	return (0);
}
