/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 22:03:31 by rruiz-la          #+#    #+#             */
/*   Updated: 2021/09/25 17:48:41 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*convert_itoa(char *str,
						size_t n_size,
						int n)
{
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	str[n_size] = '\0';
	n_size -= 1;
	while (n > 9)
	{
		str[n_size] = (n % 10) + 48;
		n /= 10;
		n_size--;
	}
	if (n < 10)
	{
		str[n_size] = n + 48;
	}
	return (str);
}

size_t	ft_nlen(int num)
{
	size_t	len;

	len = 0;
	if (num < 0)
	{
		len++;
	}
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	n_digits;

	if (n == -2147483648)
	{
		return (ft_strdup("-2147483648"));
	}
	if (n == 0)
	{
		return (ft_strdup("0"));
	}
	n_digits = ft_nlen(n);
	str = (char *)malloc((n_digits + 1) * sizeof(char));
	if (!str)
	{
		return (NULL);
	}
	convert_itoa (str, n_digits, n);
	return (str);
}
