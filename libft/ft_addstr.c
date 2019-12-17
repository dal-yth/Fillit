/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 11:54:01 by hlaineka          #+#    #+#             */
/*   Updated: 2019/10/30 11:55:13 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_addstr(char **dest, char *src)
{
	int		i;
	int		w;
	char	**returnable;

	i = 0;
	if (dest)
	{
		while (dest[i] != NULL)
			i++;
	}
	returnable = (char**)malloc(sizeof(dest) + sizeof(src) + sizeof(char) * 2);
	w = 0;
	while (w < i)
	{
		returnable[w] = ft_strdup(dest[w]);
		w++;
	}
	returnable[w] = ft_strdup(src);
	returnable[w + 1] = NULL;
	free(dest);
	return (returnable);
}
