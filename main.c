#include "fillit.h"

/*
** Ajatuksena on että main kutsuu vuorotellen ensin
** validointifunktion, joka kutsuu kaikki muut inputin tarkistukset,
** sitten tallennusfunktion, joka kutsuu funktiot tunnistamaan ja
** tallentamaan tetriminoja jonnekin ja viimeisenä solverin, joka
** kutsuu kaikki ratkaisufunktiot.
** -------------------------------------------------------------------
** Tällä hetkellä koodi on tietysti aika sekametelisoppaa ja kaikki on
** yhdessä tiedostossa, sen lisäksi luultavasti jotkin funktiot ovat
** liian pitkiä ja norminettestä en halua edes tietää :D mutta jos
** systeemin saisi jotenkin rakennettua ensin kasaan ja sitten voisi
** hienosäätää ja siistiä.
** -------------------------------------------------------------------
** Mainissa on edelliskerrasta printtilooppeja testaamista varten ja 
** paljon turhia muuttujia. Tällä hetkellä printtaa tallennetut
** tetriminot, joihin on laitettu oikeat merkit A-Z riippuen tetriminojen
** määrästä. 
*/

/*
** funktio joka näyttää usagen
*/

void	put_usage_message()
{
	ft_putendl("usage: fillit input_file");
	ft_putendl("    input_file: File containing tertimino pieces. Inputfile should follow these rules:");
	ft_putendl("    Each tetrimino is precisely 4 lines of 4 characters, each followed by a new line");
	ft_putendl("    Each character must be either a block character(’#’ ) or an empty character (’.’)");
	ft_putendl("    Your file should contain between 1 and 26 Tetriminos.");
}

int		main(int argc, char **argv)
{
	t_list			*tmins;
	int 			pieces;
	char			**field;

	tmins = NULL;
	if (argc != 2)
	{
		put_usage_message();
		return(0);
	}
	if (!(validate_input(argv)))
	{
		write(1, "invalid input", 13);
		return(0);
	}
	pieces = save_list(&tmins, argv);
	printf("%d\n", pieces);
	ft_putendl("all ok");
	solver(tmins, &field, pieces);
	print_field(&field);
	return(0);
}
