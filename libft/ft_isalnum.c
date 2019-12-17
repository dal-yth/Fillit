/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakela <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 07:50:57 by jmakela           #+#    #+#             */
/*   Updated: 2019/10/31 10:22:42 by jmakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Checks if c is alphanumeric character.
** If c is not alphanumeric, returns 0.
*/

int	ft_isalnum(int c)
{
	if (ft_isdigit(c))
		return (ft_isdigit(c));
	else if (ft_isalpha(c))
		return (ft_isalpha(c));
	else
		return (0);
}
