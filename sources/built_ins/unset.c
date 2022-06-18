/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:06:02 by tyago-ri          #+#    #+#             */
/*   Updated: 2022/06/10 21:06:02 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_from_env(char *var)
{
	int		i;
	int		n;
	char	**str;
	int		size;

	i = -1;
	n = -1;
	str = NULL;
	size = 0;
	if (find_env(var) == NULL)
		return ;
	while (g_data.exec.env[size] != NULL)
		size++;
	str = (char **) malloc (sizeof(char *) * size);
	while (g_data.exec.env[++i] != NULL)
	{
		if (!(ft_strncmp(var, g_data.exec.env[i], ft_strlen(var)) == 0 \
			&& (g_data.exec.env[i][ft_strlen(var)] == '=' \
			|| g_data.exec.env[i][ft_strlen(var)] == '\0')))
			str[++n] = ft_strdup(g_data.exec.env[i]);
	}
	str[n + 1] = NULL;
	free_split (g_data.exec.env);
	g_data.exec.env = str;
}

static int	check_unset_var(char *var)
{
	int	i;

	if (ft_isalpha(var[0]) == 0)
		return (0);
	i = 0;
	while (var[++i] != '\0')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (0);
	}
	return (1);
}

void	unset_built_in(char	**cmd)
{
	int	i;

	i = 0;
	g_data.mns.exit_code = 0;
	if (cmd[1] == NULL)
		return ;
	while (cmd[++i] != NULL)
	{
		if (check_unset_var(cmd[i]))
			remove_from_env(cmd[i]);
		else
		{
			ft_putstr_fd("unset: `", STDERR);
			ft_putstr_fd(cmd[i], STDERR);
			ft_putstr_fd("\': not a valid identifier\n", STDERR);
			g_data.mns.exit_code = 1;
		}
	}
}
