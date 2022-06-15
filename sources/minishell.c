/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 20:36:06 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/14 12:31:26 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_main g_data;

int	main(int argc, char *argv[], char *envp[])
{
	(g_data.mns).exit_code = 0;
	if (argc == 1 && argv[0] != NULL)
	{
		create_envp_list(envp);
		while (1)
		{
			exec_prompt();
			if ((g_data.mns).line[0] != '\0')
			{
				add_history((g_data.mns).line);
				//função
				if (ft_strncmp((g_data.mns).line, "exit\0", 5) == 0)
				{
					if (g_data.exec.path != NULL)
						free_path();
					if (g_data.exec.path_confirmed != NULL)
					{
						free (g_data.exec.path_confirmed);
						g_data.exec.path_confirmed = NULL;
					}					
					free ((g_data.mns).line);
					free_envp_list();
					rl_clear_history();
					clear_history();
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
