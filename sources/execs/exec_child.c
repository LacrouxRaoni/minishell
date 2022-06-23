/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:09:43 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/23 14:41:06 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exit_child(t_cmd *cmd_node, int flag)
{
	int	n;

	n = 0;
	if (flag == EACCES)
		n = 126;
	else if (flag == ENOENT)
		n = 127;
	else
		n = 127;
	perror(cmd_node->word[0]);
	free_everything();
	exit (n);
}

static void	exec_child(t_cmd *cmd_node, t_exec *exec)
{
	if (cmd_node->next != NULL)
	{
		dup2(exec->fd[1], STDOUT_FILENO);
		close (exec->fd[0]);
		close (exec->fd[1]);
	}
	if (cmd_node->fd_out > 0)
		dup2(cmd_node->fd_out, STDOUT_FILENO);
	if (check_if_built_in(cmd_node) == 0)
	{
		if (exec->path_confirmed != NULL)
		{
			if (execve(exec->path_confirmed, cmd_node->word, exec->env) - 1)
				exit_child(cmd_node, errno);
		}
	}
	else
		exec_built_in(cmd_node);
	free_everything();
	exit(0);
}

static void	check_child_exit_code(int wstatus)
{
	if ((g_data.mns).exit_code == 0)
		(g_data.exec).in_exec = 5;
	if (!WIFEXITED(wstatus))
		(g_data.mns).exit_code = WEXITSTATUS(wstatus);
	if (g_data.exec.in_exec == 1)
		(g_data.mns).exit_code = 130;
	else if (g_data.exec.in_exec == 5)
		(g_data.mns).exit_code = 0;
}

static void	redirect_to_pipe_and_free_path(t_cmd *cmd_node,
		t_exec *exec, int wstatus)
{
	if (cmd_node->next != NULL)
	{
		dup2(exec->fd[0], STDIN_FILENO);
		close (exec->fd[0]);
		close (exec->fd[1]);
	}
	else
	{
		waitpid(exec->pid, &wstatus, 0);
		(g_data.mns).exit_code = WEXITSTATUS(wstatus);
	}
	if (g_data.exec.pid != 0 && g_data.exec.in_exec == 1)
		(g_data.mns).exit_code = 130;
	if (exec->path_confirmed != NULL)
	{
		free (exec->path_confirmed);
		exec->path_confirmed = NULL;
	}
	if (exec->path != NULL)
		free_path();
}

void	call_child_process(t_cmd *cmd_node)
{
	t_exec	*exec;
	int		wstatus;

	exec = &(g_data.exec);
	exec->pid = fork();
	if (exec->pid < 0)
		exit (write (1, "Fork error\n", 14));
	if (exec->pid == 0)
		exec_child(cmd_node, exec);
	waitpid(exec->pid, &wstatus, 0);
	check_child_exit_code(wstatus);
	redirect_to_pipe_and_free_path(cmd_node, exec, wstatus);
}
