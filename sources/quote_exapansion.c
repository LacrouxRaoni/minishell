/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_exapansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 18:18:10 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/27 21:11:53 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_expansion(t_cmd *cmd_node, int i)
{
	int	j;

	j = 0;
	while (cmd_node->word[i][j])
	{
		if (cmd_node->word[i][j] == '\'')
		{
			handle_s_quote(cmd_node, i);
			break ;
		}
		else if (cmd_node->word[i][j] == '\"')
		{
			handle_d_quotes(cmd_node, i);
			break ;
		}
		j++;
	}
}
