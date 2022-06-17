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

void	abort_sig(int sig __attribute__((unused)))
{
	write (1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(g_data.exec).error = 130;
}

void	kill_loop(int signum)
{
	(void)signum;
	if (g_data.exec.b_hdoc == 1)
	{
		close (STDIN);
		g_data.mns.err_num = 1;
	}
	if (g_data.exec.pid != 0 && g_data.exec.in_exec == 1)
	{
		kill(g_data.exec.pid, SIGKILL);
		write (1, "\n", 1);
	}
}

void	quit_core(int signum)
{
	(void)signum;
	if (g_data.exec.pid != 0 && g_data.exec.in_exec == 1)
	{
		free_envp_list();
		kill(g_data.exec.pid, SIGKILL);
		ft_putstr_fd("Quit (Core dumped)\n", 1);
	}
}
