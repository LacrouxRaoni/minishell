/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:36:40 by tyago-ri          #+#    #+#             */
/*   Updated: 2022/05/23 22:36:40 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd_built_in(void)
{
	char	*str;

	g_data.mns.exit_code = 0;
	str = malloc (1024);
	ft_putstr_fd(getcwd(str, 1024), STDOUT);
	write (1, "\n", 1);
	free (str);
	return ;
}
