/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 20:36:06 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/22 01:10:51 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_main	g_data;

static void	start_minishell(char **envp)
{
	g_data.exec.env = workspace_env(envp);
	create_envp_list();
	signal (SIGINT, kill_loop);
	while (1)
	{
		signal (SIGQUIT, SIG_IGN);
		(g_data.exec).in_exec = 0;
		exec_prompt();
		if ((g_data.mns).line == NULL)
		{
			rl_clear_history();
			free_envp_list();
			write (1, "exit\n", 5);
			exit (0);
		}
		if ((g_data.mns).line[0] != '\0' && (g_data.mns).line != NULL)
		{
			(g_data.exec).in_exec = 1;
			signal (SIGQUIT, quit_core);
			add_history((g_data.mns).line);
			parsing_and_exec();
		}
		else
			free ((g_data.mns).line);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc == 1 && argv[0] != NULL)
		start_minishell(envp);
	else
	{
		ft_putstr_fd("Invalid arguments\n", 1);
		return (1);
	}
	return (0);
}
