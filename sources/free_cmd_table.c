/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 21:20:42 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/24 22:07:59 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_sublines(t_cmd **cmd, int i)
{
	if ((*cmd)->word != NULL)
	{
		i = -1;
		while ((*cmd)->word[++i])
			free((*cmd)->word[i]);
		free ((*cmd)->word);
		(*cmd)->word = NULL;
	}
	if ((*cmd)->redirect != NULL)
	{
		i = -1;
		while ((*cmd)->redirect[++i])
			free((*cmd)->redirect[i]);
		free ((*cmd)->redirect);
		(*cmd)->redirect = NULL;
	}
}

void	free_cmd_table(t_cmd **cmd)
{
	int		i;
	t_cmd	*temp;

	if ((*cmd) != NULL)
	{
		while ((*cmd) != NULL)
		{
			free_sublines(cmd, i);
			if ((*cmd)->var_name != NULL)
				free((*cmd)->var_name);
			if ((*cmd)->content != NULL)
				free((*cmd)->content);
			temp = (*cmd);
			(*cmd) = temp->next;
			free (temp);
		}
	}
}
