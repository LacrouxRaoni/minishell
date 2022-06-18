/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 21:20:42 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/18 19:49:36 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_sublines(t_cmd *cmd, int i)
{
	if (cmd->word != NULL)
	{
		i = -1;
		while (cmd->word[++i])
			free(cmd->word[i]);
		free (cmd->word);
		cmd->word = NULL;
	}
	if (cmd->redirect != NULL)
	{
		i = -1;
		while (cmd->redirect[++i])
			free(cmd->redirect[i]);
		free (cmd->redirect);
		cmd->redirect = NULL;
	}
}

void	free_cmd_table(void)
{
	int		i;
	t_cmd	*temp;
	t_cmd	*cmd;

	i = 0;
	cmd = g_data.cmd;
	if (cmd != NULL)
	{
		while (cmd != NULL)
		{
			free_sublines(cmd, i);
			temp = cmd;
			cmd = temp->next;
			free (temp);
		}
		free (cmd);
	}
}
