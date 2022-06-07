/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_key_n_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:39:52 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/03 14:10:54 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key(char *key_line)
{
	int		i;
	char	*key;

	key = '\0';
	i = 0;
	while (key_line[i] != '=')
		i++;
	key = ft_substr(key_line, 0, i);
	return (key);
}

char	*extract_value(char *value_line)
{
	int		i;
	char	*value;	

	value = NULL;
	i = 0;
	while (value_line[i] != '=')
		i++;
	value = ft_substr(value_line, i + 1, ft_strlen(value_line) - i);
	return (value);
}
