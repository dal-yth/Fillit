#ifndef FILLIT_H
# define FILLIT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/includes/libft.h"

/*
** Listan structi.
*/

typedef struct		s_list
{
	char			**data;
	struct s_list	*next;
}					t_list;

/*
** Structi johon tallennetaan tietoja inputin tarkistamiseen.
** Pisteiden, hashtagien, newlinejen, viereisten palojen,
** palojen kokonaismäärä ja luettujen merkkien määrä.
*/

typedef struct	s_valid
{
	int 		dot;
	int			hash;
	int			newl;
	int			sides;
	int			ret;
}				t_valid;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

/*
** validate.c funktiot
** tarkistavat inputin
*/

void 			init_struct(t_valid *ok);
int 			validate_tetri(char *buf, t_valid *ok);
int 			check_buf(char *buf, t_valid *ok, int ret);
int 			validate_input(char **argv);

/*
** fillit.c funktiot
** luovat linked listin
*/

char 			*mod_buf(char *buf, char c);
t_list 			*newnode(char **data);
void			append(t_list **tetris, char **data);
int				save_list(t_list **tetris, char **argv);

/*
** solverin funktiot
** ratkaisevat ongelman
*/

void			solver(t_list *tmins, char ***field, int size);
int				make_field(char ***field, int field_size, int pieces);

/*
** extrajutut
** printer on vain testausta varten
*/

void			printer(t_list *tetris);
void			put_usage_message();
void			print_field(char ***field);
char			*ft_strset(char value, size_t num);

#endif
