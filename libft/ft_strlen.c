/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:10:07 by jmakela           #+#    #+#             */
/*   Updated: 2019/10/31 10:41:14 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Calculates length of string s, excluding null byte.
** Returns the number of bytes in string.
*/

unsigned long	ft_strlen(char const *s)
{
	unsigned long i;

	i = 0;
	while (s[i] != '\0')
		i = i + 1;
	return (i);
}
