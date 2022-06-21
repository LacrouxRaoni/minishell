/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_redirectsc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:36:22 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/21 15:51:53 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	open_pipe(void)
{
	t_exec	*exec;

	exec = &(g_data.exec);
	if (pipe(exec->fd) < 0)
		exit (write (1, "Pipe error\n", 14));
}

int	init_redirects(t_cmd *cmd_node)
{
	exec_redirect(cmd_node);
	if ((g_data.mns).exit_code == 0)
		dup2(cmd_node->fd_in, STDIN_FILENO);
	if ((g_data.mns).exit_code == 1)
	{
		if (cmd_node->fd_in < 0 || cmd_node->fd_out < 0)
		{
			if (cmd_node->next != NULL)
			{
				dup2(g_data.exec.fd[0], STDIN_FILENO);
				close (g_data.exec.fd[0]);
				close (g_data.exec.fd[1]);
				return (0);
			}
			else
				return (1);
		}
	}
	return (0);
}

void	close_files(t_cmd *cmd_node)
{
	if (cmd_node->fd_in > 0)
		close (cmd_node->fd_in);
	if (cmd_node->fd_out > 0)
		close (cmd_node->fd_out);
	if (cmd_node->fd_in < 0 || cmd_node->fd_out < 0)
		(g_data.mns).exit_code = 1;
}
