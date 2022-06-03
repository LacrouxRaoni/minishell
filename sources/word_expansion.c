/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:01:02 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/03 12:02:35 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	word_expansion(t_cmd *cmd_node)
{
	int		i;

	i = 0;
	if (cmd_node != NULL)
	{
		while (cmd_node->word[i] != NULL)
		{	
			if (ft_strchr(cmd_node->word[i], '=') != NULL)
			{
				//mudar de lugar
				check_for_var(cmd_node, i);
				i++;
			}
			else if (cmd_node->word[i][0] == '~')
			{
				if (tild_expansion(cmd_node, i) == 1)
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
		}
	}
}
