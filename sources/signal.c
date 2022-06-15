/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:34:54 by tyago-ri          #+#    #+#             */
/*   Updated: 2022/06/10 18:34:54 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	kill_loop(int signum)
{
	(void)signum;
	if (g_data->here_doc == 1)
	{
		close (STDIN);
		g_data.mns.err_num = 1;
	}
	if (g_data.exec.exec_pid != 0 && g_data->in_exec == 1)
	{
		kill(g_data->exec_pid, SIGKILL);
		write (1, "\n", 1);
	}
	if (g_data->in_exec == 0)
	{
		write (1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_data.mns.exit_code = 130;
}

void	quit_core(int signum)
{
	(void)signum;
	if (g_data->exec_pid != 0 && g_data->in_exec == 1)
	{
		kill(g_data->exec_pid, SIGKILL);
		ft_putstr_fd("Quit (Core dumped)\n", 1);
	}
}