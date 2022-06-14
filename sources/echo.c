/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 23:38:14 by tyago-ri          #+#    #+#             */
/*   Updated: 2022/05/23 23:38:14 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_built_in(char **cmd)
{
	t_exec	exec;
	t_cmd	*node;
	int	i;

	node = g_data.cmd;
	i = 1;
	if (cmd[1] == NULL)
	{
		printf ("\n");
	}
	else
	{
		if (ft_str_check(cmd[1], "-n"))
			i++;
		while (cmd[i] != NULL)
		{
			if (cmd[i][0] != '\0')
			{
				printf ("%s", cmd[i]);
			}
			if (cmd[i + 1] != NULL)
			{
				printf (" ");
			}
			i++;
		}
		if ((ft_str_check(cmd[1], "-n")) == 0)
		{
			printf ("\n");
		}
	}
	g_data.mns.exit_code = 0;
	return ;
}
