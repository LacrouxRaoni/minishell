/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:18:10 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/23 19:01:42 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	quote_expansion(t_cmd *cmd_node, int i)
{
	int	j;

	j = 0;
	while (cmd_node->word[i][j])
	{
		if (cmd_node->word[i][j] == '\'')
		{
			if (handle_s_quote(cmd_node, i) < 0)
				return (-2);
			return (0);
		}
		else if (cmd_node->word[i][j] == '\"')
		{
			if (handle_d_quotes(cmd_node, i) < 0)
				return (-1);
			else
				return (0);
		}
		j++;
	}
	return (0);
}
