/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:33:28 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/15 00:49:31 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	print_terminal_line();
	(g_data.mns).line = readline((g_data.mns).line_cmd);
	free ((g_data.mns).line_cmd);
	(g_data.mns).exit_code = 0;
}
