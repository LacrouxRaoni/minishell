/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_superjoin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:09:54 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/11 22:09:09 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	transfer_from_src_to_dst(char **src, char **dst, int total_len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (k < total_len)
	{
		if (src[i][j] == '\0')
		{
			i++;
			j = 0;
		}
		(*dst)[k] = src[i][j];
		j++;
		k++;
	}
	(*dst)[k] = '\0';
}

char	*ft_str_superjoin(char **src)
{
	int		i;
	int		len;
	int		total_len;
	char	*dst;

	total_len = 0;
	len = 0;
	i = 0;
	while (src[i])
	{
		len = ft_strlen(src[i]);
		total_len = total_len + len;
		i++;
	}
	dst = (char *)ft_calloc(total_len +1, sizeof(char *));
	if (!dst)
		return (NULL);
	transfer_from_src_to_dst (src, &dst, total_len);
	return (dst);
}
