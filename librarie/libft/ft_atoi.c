/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 21:59:37 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/02/12 14:32:14 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n'
		|| c == '\v' || c == '\f'
		|| c == '\r' || c == ' ')
	{
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	str;
	int	negative;

	negative = 0;
	str = 0;
	while (ft_isspace(*nptr))
	{
		nptr++;
	}
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			negative = 1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		str = (str * 10) + (*nptr++ - 48);
	}
	if (negative)
		return (str * -1);
	return (str);
}
