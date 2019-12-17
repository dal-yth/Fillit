/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 13:36:00 by jmakela           #+#    #+#             */
/*   Updated: 2019/11/05 14:55:11 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Compares strings s1 and s2.
** Returns int less than, equal, or greater than zero if s1 is found,
** to be less than, equal, or greater than s2.
*/

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *ptr1;
	unsigned char *ptr2;

	if (n == 0)
		return (0);
	ptr1 = (unsigned char*)s1;
	ptr2 = (unsigned char*)s2;
	n = n - 1;
	while ((*ptr1 && (*ptr1 == *ptr2)) && n)
	{
		n = n - 1;
		if (*ptr1 != *ptr2)
			return (*ptr1 - *ptr2);
		ptr1 = ptr1 + 1;
		ptr2 = ptr2 + 1;
	}
	return (*ptr1 - *ptr2);
}
