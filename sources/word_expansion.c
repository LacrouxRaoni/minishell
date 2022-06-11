/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:01:02 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/11 15:48:03 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_expansion_type(t_cmd *cmd_node, int i)
{
	if (ft_strchr(cmd_node->word[i], '=') != NULL)
	{
		check_for_var(cmd_node, i);
	}
	else if (cmd_node->word[i][0] == '~')
	{
		tild_expansion(cmd_node, i);
		cmd_node->expansion++;
	}
	else if ((ft_strchr(cmd_node->word[i], '\'') != NULL)
		|| (ft_strchr(cmd_node->word[i], '\"') != NULL))
	{
		if (quote_expansion(cmd_node, i) < 0)
			return (-1);
	}
	else if (ft_strchr(cmd_node->word[i], '$') != NULL)
	{
		if (parse_assignment_expansion(cmd_node, i) == -1)
			return (-1);
	}
	return (i);
}

int	word_expansion(void)
{
	int		i;
	t_cmd	*cmd_node;

	cmd_node = g_data.cmd;
	while (cmd_node != NULL)
	{
		i = 0;
		while (cmd_node->word[i] != NULL)
		{
			check_expansion_type(cmd_node, i);
			if (i < 0)
				return (-1);
			i++;
		}
		cmd_node = cmd_node->next;
	}
}
