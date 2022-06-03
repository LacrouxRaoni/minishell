/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 22:06:49 by tyago-ri          #+#    #+#             */
/*   Updated: 2022/05/23 22:06:49 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cp_first_env(char **env)
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
