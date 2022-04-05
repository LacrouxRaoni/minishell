/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 22:01:06 by rruiz-la          #+#    #+#             */
/*   Updated: 2021/10/20 20:53:30 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	tot_size;
	size_t	*pos;
	int		fill_bite;

	tot_size = nmemb * size;
	fill_bite = 0;
	pos = malloc(tot_size);
	if (!pos || (tot_size > __INT_MAX__))
	{
		return (NULL);
	}
	ft_memset (pos, fill_bite, tot_size);
	return ((void *) pos);
}
