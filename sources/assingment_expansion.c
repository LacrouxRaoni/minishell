/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assingment_expansion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:00:48 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/16 14:29:22 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_key_value(char **dollar)
{
	t_env_list	*node;

	node = g_data.list;
	if (ft_strcmp(*dollar, "?") == 0)
	{
		free (*dollar);
		*dollar = ft_itoa((g_data.exec).error);
		return (0);
	}	
	while (node != NULL)
	{
		if (ft_strcmp(node->key, *dollar) == 0)
		{
			free (*dollar);
			*dollar = ft_strdup(node->value);
			return (0);
		}
		node = node->next;
	}
	free (*dollar);
	*dollar = ft_strdup("");
	(g_data.mns).exit_code = -3;
	return (0);
}

char	*assignment_expansion(char *assi_word)
{
	int		j;
	char	*dollar;

	j = 0;
	dollar = NULL;
	if (assi_word[j] == '$')
	{
		if (assi_word[j + 1] == '{')
		{
			while (assi_word[j] != '}')
			{
				if (assi_word[j] == '\0')
					return (NULL);
				j++;
			}
			dollar = ft_substr(assi_word, 2, j - 2);
		}	
		else
			dollar = ft_substr(assi_word,
					1, ft_strlen(assi_word));
	}
	expand_key_value(&dollar);
	return (dollar);
}
