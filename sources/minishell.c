/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 20:36:06 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/16 17:02:39 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_main	g_data;

int	main(int argc, char *argv[], char *envp[])
{
	(g_data.mns).exit_code = 0;
	if (argc == 1 && argv[0] != NULL)
	{
		create_envp_list(envp);
		signal (SIGINT, kill_loop);
		while (1)
		{
			signal (SIGQUIT, SIG_IGN);
			(g_data.exec).in_exec = 0;
			exec_prompt();
			if ((g_data.mns).line[0] != '\0')
			{
				signal (SIGQUIT, quit_core);
				(g_data.exec).in_exec = 1;
				add_history((g_data.mns).line);
				if (g_data.list->d_exit == 1)
				{
					free_envp_list();
					exit (0);
				}
				parsing_and_exec();
			}
			else
				free ((g_data.mns).line);
		}
	}
	else
	{
		ft_putstr_fd("Invalid arguments\n", 1);
		return (1);
	}
	return (0);
}
