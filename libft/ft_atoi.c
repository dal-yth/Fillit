/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 13:23:07 by jmakela           #+#    #+#             */
/*   Updated: 2019/11/05 13:20:57 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Convert the initial portion of string pointed to by nptr to int.
** Returns the converted value.
*/

static int	ft_convert(const char *nptr, int result, size_t i, int neg)
{
	while (i < ft_strlen(nptr))
	{
		if (ft_isdigit(nptr[i]) == 0)
			return (result * neg);
		result = result * 10 + (nptr[i] - '0');
		i = i + 1;
	}
	return (result * neg);
}

int			ft_atoi(const char *nptr)
{
	size_t	i;
	int		neg;
	int		result;

	i = 0;
	neg = 1;
	result = 0;
	while (nptr[i] == 32 || (nptr[i] > 8 && nptr[i] < 14))
		i = i + 1;
	if (ft_isdigit(nptr[i]) == 0 && nptr[i] != '-' && nptr[i] != '+')
		return (0);
	if (ft_strcmp(nptr, "-2147483648") == 0)
		return (-2147483648);
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = neg * -1;
		i = i + 1;
	}
	result = ft_convert(nptr, result, i, neg);
	return (result);
}
