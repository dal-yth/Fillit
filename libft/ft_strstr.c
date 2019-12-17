/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 08:00:05 by jmakela           #+#    #+#             */
/*   Updated: 2019/11/05 14:56:36 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Finds the first occurrence of the substring needle in the string haystack.
** Returns a pointer to the beginning of the substring,
** or NULL is substring is not found.
*/

char	*ft_strstr(char const *haystack, char const *needle)
{
	size_t	j;

	j = ft_strlen(needle);
	if (j == 0)
		return ((char*)haystack);
	while (*haystack)
	{
		if (*haystack == *needle)
		{
			if (ft_strncmp(needle, haystack, j) == 0)
				return ((char*)haystack);
		}
		haystack = haystack + 1;
	}
	return (NULL);
}
