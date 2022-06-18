/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_assingment_expansion_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:14:27 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/18 19:49:36 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_keys(char *word, int j)
{
	while (word[j] != '}')
	{
		if (word[j] == '\0')
			return (-1);
		j++;
	}
	j++;
	return (j);
}

int	count_dollars(t_cmd *cmd_node, int i, int *len, int *k)
{
	(*len)++;
	if (cmd_node->word[i][(*len)] == '{')
	{
		(*len) = count_keys(cmd_node->word[i], (*len));
		if ((*len) < 0)
			return (-1);
		else
			(*k)++;
	}
	else
	{
		while (cmd_node->word[i][(*len)] != ' '
			&& cmd_node->word[i][(*len)] != '$'
			&& cmd_node->word[i][(*len)] != '{'
			&& cmd_node->word[i][(*len)] != '}'
			&& cmd_node->word[i][(*len)] != '\0')
			(*len)++;
		(*k)++;
	}
	return (0);
}

void	free_aux_assig(char ***tmp)
{
	int	i;

	i = -1;
	while ((*tmp)[++i])
		free ((*tmp)[i]);
	free ((*tmp));
	(*tmp) = NULL;
}
