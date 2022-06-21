/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 02:32:57 by tyago-ri          #+#    #+#             */
/*   Updated: 2022/06/17 02:32:57 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**copy_env(char **env)
{
	char	**ret;
	int		i;
	int		n;

	i = 0;
	n = -1;
	while (env[i] != NULL)
		i++;
	ret = (char **) malloc (sizeof(char *) * (i + 1));
	while (env[++n] != NULL)
		ret[n] = ft_strdup(env[n]);
	ret[n] = NULL;
	return (ret);
}

char	*find_env(char *var)
{
	int		i;

	i = 0;
	while (g_data.exec.env[i] != NULL)
	{
		if (ft_strncmp(var, g_data.exec.env[i], ft_strlen(var)) == 0 \
		&& (g_data.exec.env[i][ft_strlen(var)] == '=' \
		|| g_data.exec.env[i][ft_strlen(var)] == '\0'))
		{
			if (g_data.exec.env[i][ft_strlen(var)] == '=')
				return (g_data.exec.env[i] + ft_strlen(var) + 1);
			else
				return ("\0");
		}
		i++;
	}
	return (NULL);
}

char	**get_sorted_env(void)
{
	int		env_size;
	char	**env;
	int		i;
	char	*temp;

	env = copy_env(g_data.exec.env);
	env_size = 0;
	while (env[env_size] != NULL)
		env_size++;
	while (env_size > 0)
	{
		i = 0;
		while (i < env_size - 1)
		{
			if (ft_strncmp(env[i], env[i + 1], ft_strlen(env[i])) > 0)
			{
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
			}
			i++;
		}
		env_size--;
	}
	return (env);
}

char	**workspace_env(char **env)
{
	char	**ret;
	int		i;
	int		n;

	i = -1;
	n = 0;
	while (env[++i] != NULL)
	{
		if (ft_strnstr(env[i], "WORKSPACE", ft_strlen(env[i])) == NULL)
			n++;
	}
	ret = (char **) malloc (sizeof(char *) * (n + 1));
	n = -1;
	i = 0;
	while (env[++n] != NULL)
	{
		if (ft_strnstr(env[n], "WORKSPACE", ft_strlen(env[n])) == NULL)
			ret[i++] = ft_strdup(env[n]);
	}
	ret[i] = NULL;
	return (ret);
}

void	env_built_in(char **cmd)
{
	int	i;

	if (cmd[1] != NULL)
	{
		ft_putstr_fd("env: too many arguments\n", STDERR);
		(g_data.mns).exit_code = 1;
		return ;
	}
	else
	{
		i = -1;
		while (g_data.exec.env[++i] != NULL)
		{
			if (ft_strchr(g_data.exec.env[i], '=') != NULL)
				printf ("%s\n", g_data.exec.env[i]);
		}
		(g_data.mns).exit_code = 0;
		return ;
	}
}
