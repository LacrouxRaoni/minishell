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
	int	i;

	i = 1;
	if (cmd[1] == NULL)
		write (1, "\n", 1);
	else
	{
		if (ft_str_check(cmd[1], "-n"))
			i++;
		while (cmd[i] != NULL)
		{
			if (cmd[i][0] != '\0')
				ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1] != NULL)
				write (1, " ", 1);
			i++;
		}
		if ((ft_str_check(cmd[1], "-n")) == 0)
			write (1, "\n", 1);
	}
	g_data.mns.exit_code = 0;
	return ;
}
