/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:01:02 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/18 19:49:36 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_expansion_type(t_cmd *cmd_node, int i)
{
	if (cmd_node->word[i][0] == '~')
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
		if (parse_assignment_expansion(cmd_node, i) < 0)
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
			if (check_expansion_type(cmd_node, i) < 0)
				return (-1);
			else if ((g_data.mns).exit_code == -3)
				return (-2);
			i++;
		}
		cmd_node = cmd_node->next;
	}
	return (0);
}
