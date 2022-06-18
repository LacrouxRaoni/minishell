/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_redirectsc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 11:36:22 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/18 19:49:36 by tyago-ri         ###   ########.fr       */
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

void	init_redirects(t_cmd *cmd_node)
{
	exec_redirect(cmd_node);
	if ((g_data.mns).exit_code == 0)
		dup2(cmd_node->fd_in, STDIN_FILENO);
}

void	close_files(t_cmd *cmd_node)
{
	if (cmd_node->fd_in > 0)
		close (cmd_node->fd_in);
	if (cmd_node->fd_out > 0)
		close (cmd_node->fd_out);
}
