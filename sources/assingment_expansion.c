/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assingment_expansion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 10:00:48 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/10 10:17:16 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_key_in_hash(char **dollar, int r)
{
	t_hash	*h_list;
	int		index;

	if (g_data.hash[(r)]->size == 0)
	{
		free (*dollar);
		*dollar = ft_strdup("");
		return (1);
	}
	index = get_hash_pos(*dollar, g_data.hash[(r)]->size);
	h_list = g_data.hash[(r)];
	while (h_list->list[index])
	{
		if (ft_strcmp(h_list->list[index]->key, *dollar) > 0)
			h_list->list[index] = h_list->list[index]->next;
		else
		{
			free (*dollar);
			*dollar = ft_strdup(h_list->list[index]->value);
			return (0);
		}
	}
}
static int	expand_key_value(char **dollar)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (r < 2)
	{
		check_key_in_hash(dollar, r);
		if (i == 1)
			return (1);
		else
			return (0);
		r++;
	}
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
