/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:33:28 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/18 19:49:36 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_line(void)
{
	if ((g_data.mns).line != NULL)
	{
		free ((g_data.mns).line);
		(g_data.mns).line = NULL;
	}
}

void	print_terminal_line(void)
{
	char	*user;
	char	dir[1024];
	char	*aux;
	char	*aux2;

	user = getenv("USER");
	getcwd(dir, sizeof(dir));
	aux = ft_strjoin(user, "@:");
	aux2 = ft_strjoin(dir, "$ ");
	(g_data.mns).line_cmd = ft_strjoin(aux, aux2);
	free (aux);
	free (aux2);
}

void	exec_prompt(void)
{
	(g_data.exec).error = (g_data.mns).exit_code;
	g_data.mns.exit_code = 0;
	print_terminal_line();
	(g_data.mns).line = readline((g_data.mns).line_cmd);
	free ((g_data.mns).line_cmd);
}
