/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:01:02 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/03 14:36:22 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_expansion_type(t_cmd *cmd_node, int i)
{
	if (ft_strchr(cmd_node->word[i], '=') != NULL)
	{
		//mudar de lugar
		check_for_var(cmd_node, i);
		i++;
	}
	else if (cmd_node->word[i][0] == '~')
	{
		tild_expansion(cmd_node, i);
		i++;
	}
	else if ((ft_strchr(cmd_node->word[i], '\'') != NULL)
		|| (ft_strchr(cmd_node->word[i], '\"') != NULL))
	{
		quote_expansion(cmd_node, i);
		i++;
	}
	else if (ft_strchr(cmd_node->word[i], '$') != NULL)
	{
		parse_assignment_expansion(cmd_node, i);
		i++;
	}
	else
		i++;
	return (i);
}

void	word_expansion(t_cmd *cmd_node)
{
	int		i;

	i = 0;
	if (cmd_node != NULL)
	{
		while (cmd_node->word[i] != NULL)
		{	
			i = check_expansion_type(cmd_node, i);
		}
	}
}
