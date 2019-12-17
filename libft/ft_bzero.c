/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 11:39:12 by jmakela           #+#    #+#             */
/*   Updated: 2019/10/31 10:24:46 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Erases data in the n bytes of memory.
** Starting at the location pointed by s.
** Void pointer is cast as char*.
** Values pointed by char *s are made into '\0' chars.
*/

void	ft_bzero(void *s, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		((char*)s)[i] = '\0';
		i = i + 1;
	}
}
