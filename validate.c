/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:06:18 by jmakela           #+#    #+#             */
/*   Updated: 2019/12/12 18:06:18 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Alustetaan structin arvot nollaksi.
** Ilman alustusta tuli villejä satojen tuhansien arvoja :D
*/

void	init_struct(t_valid *ok)
{
	ok->dot = 0;
	ok->hash = 0;
	ok->newl = 0;
	ok->sides = 0;
	ok->ret = 0;
}

/*
** Tarkistetaan että luettu tetrimino on todellinen tetrimino.
** Kun löydetään hashtag, tarkistetaan onko sen sivuilla myös hashtageja.
** Jos hashtag löytyy, kasvatetaan koskettavien sivujen määrää.
** Kaikilla muilla tetriminoilla paitsi neliöllä koskettavia sivuja on 6
** ja neliöllä niitä on 8. Jos ok.sides määrä on siis 6 tai 8 tetrimino on ok.
** Tätä ennen on tarkistettu check_buf funktiossa että hashtageja on oikea määrä.
*/
 
int validate_tetri(char *buf, t_valid *ok)
{
	int i;

	i = 0;
	while(i <= 18)
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
		return(1);
	return(0);
}

/*
** Tarkistetaan luettu 21 (tai 20) merkkiä.
** Jos löytyy vääriä merkkejä palautetaan 0.
** Count laskurilla tarkastellaan aina rivin 4 ensimmäistä merkkiä.
** Ainoastaan jos näissä 4 merkissä on pisteitä tai hashtageja,
** ne lisätään kokonaismäärään. Vastaavasti newlinet täytyy löytyä
** aina joka viidentenä charina tai viimeisenä charina.
** Tarkistetaan että kaikkien merkkien määrät ovat oikein,
** muutoin palautetaan 0. Ret == 20 tarkistus on viimeistä tetriminoa
** varten. Ohjeessa sanotaan että oikeassa tetriminossa on aina
** 4 merkkiä ja newline rivillä, ja kahden tetriminon välissä on newline.
** Täten viimeinen tetrimino on erikoistapaus koska sen jälkeen ei tule
** uutta tetriminoa, ei tule myöskään uutta newlineä, täten viimeinen read
** pitäisi aina olla 20 merkkiä ja newlinejä yksi vähemmän.
*/

int check_buf(char *buf, t_valid *ok, int ret)
{
	int i;
	int count;

	i = 0;
	count = 1;
	if(!buf)
		return(0);
	while (buf[i])
	{
		if (buf[i] != '.' && buf[i] != '#' && buf[i] != '\n')
			return(0);
		if (buf[i] == '.' && count <= 4)
			ok->dot = ok->dot + 1;
		if (buf[i] == '#' && count <= 4)
			ok->hash = ok->hash + 1;
		if (buf[i] == '\n' && ((i + 1) % 5 == 0 || i == 20))
		{
			ok->newl = ok->newl + 1;
			count = 0;
		}
		i = i + 1;
		count = count + 1;
	}
	if (ret == 20)
	{
		if (!(ok->dot == 12 && ok->hash == 4 && ok->newl == 4))
			return(0);
		return(1);
	}
	if (!(ok->dot == 12 && ok->hash == 4 && ok->newl == 5))
		return(0);
	return(1);
}

/*
** Validate_input funktio kutsuu kaikki muut funktiot, jotka
** testaavat inputin oikeellisuuden.
** BUFF_SIZE on 21. Ensin alustetaan structi, jonka jälkeen
** avataan tiedosto ja luetaan. Check_buf tarkistaa merkit ja
** validate_tetri tarkistaa että merkeistä koostuu tetriminoja.
** Tarkistetaan että tetriminojen määrä on korkeintaan 26.
** Ok.ret arvolla tarkistetaan viimeinen tetrimino,
** viimeisessä readissa pitäisi aina olla vain 20 merkkiä,
** joten jos viimeisen tetriminon jälkeen on newline,
** jonka tarkistus muuten päästää läpi normaalina tetriminona,
** se juuttuu ok.ret tarkistukseen.
** Pitäisikö viimeisessä versiossa return(0) korvata exitillä?
*/

int validate_input(char **argv)
{
	int fd;
	int tcount;
	int ret;
	char buf[BUFF_SIZE + 1];
	t_valid *ok;

	tcount = 0;
	ok = (t_valid*)malloc(sizeof(t_valid));
	ret = 0;
	fd = open(argv[1], O_RDONLY);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		init_struct(ok);
		ok->ret = ret;
		buf[ret] = '\0';
		if (!(check_buf(buf, ok, ret)))
			return(0);
		if (!(validate_tetri(buf, ok)))
			return(0);
		tcount = tcount + 1;
		if (tcount > 26)
			return(0);
	}
	close(fd);
	if (ok->ret != 20)
		return(0);
	free(ok);
	return(1);
}
