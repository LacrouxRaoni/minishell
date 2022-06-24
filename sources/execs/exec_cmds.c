/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:26:53 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/23 22:10:09 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_exec(void)
{
	g_data.exec.temp_fd = dup(STDIN_FILENO);
	g_data.exec.path_confirmed = NULL;
	g_data.exec.path = NULL;
	g_data.exec.b_hdoc = 0;
}

void	free_everything(void)
{
	free_cmd_table();
	free_lexical_line();
	rl_clear_history();
	free_envp_list();
	if (g_data.exec.path != NULL)
		free_path();
	if (g_data.exec.path_confirmed != NULL)
	{
		free (g_data.exec.path_confirmed);
		g_data.exec.path_confirmed = NULL;
	}
	free_line();
}

static int	run_cmd(t_cmd *cmd_node, int i)
{
	if (cmd_node->next != NULL)
		open_pipe();
	if (cmd_node->redirect[i] != NULL)
	{
		if (init_redirects(cmd_node) == 1)
			return (1);
	}
	if (cmd_node->word[i] != NULL && (g_data.mns).exit_code == 0)
	{
		if (check_n_exec_special_built_in(cmd_node) == 0)
			return (0);
		if (check_if_built_in(cmd_node) == 0 && g_data.mns.exit_code == 0)
		{
			if (get_path(cmd_node, i) == 1)
				return (1);
		}
		call_child_process(cmd_node);
	}
	return (0);
}

void	exec_cmd(void)
{
	t_cmd	*cmd_node;
	int		i;

	init_exec();
	cmd_node = g_data.cmd;
	i = 0;
	while (cmd_node != NULL)
	{
		if (run_cmd(cmd_node, i) == 1)
			break ;
		close_files(cmd_node);
		if (cmd_node->next != NULL)
			(g_data.mns).exit_code = 0;
		cmd_node = cmd_node->next;
	}
	dup2(g_data.exec.temp_fd, STDIN_FILENO);
	close (g_data.exec.temp_fd);
}
