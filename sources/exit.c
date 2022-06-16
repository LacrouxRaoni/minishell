/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 18:43:14 by tyago-ri          #+#    #+#             */
/*   Updated: 2022/06/10 18:43:14 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_built_in(char **cmd)
{
	int	status;

	if (g_data.cmd->next != NULL)
		return ;
	g_data.list->d_exit = 1;
	write (1, "exit\n", 5);
	if (cmd[1] != NULL && ft_str_isnum(cmd[1]) == 0)
	{
		g_data.mns.exit_code = 2;
		ft_putstr_fd("exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putstr_fd(": numeric argument required\n", STDERR);
	}
	else if (cmd[1] != NULL && cmd[2] != NULL)
	{
		g_data.mns.exit_code = 1;
		ft_putstr_fd("exit: too many arguments\n", STDERR);
	}
	else if (cmd[1] != NULL && ft_str_isnum(cmd[1]) == 1)
		g_data.mns.exit_code = ft_atoi(cmd[1]);
	status = g_data.mns.exit_code;
	free_everything();
	exit(status);
}
