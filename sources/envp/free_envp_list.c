/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envp_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:21:09 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/20 16:59:03 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_envp(void)
{
	t_exec	*envp;
	int		i;

	envp = &(g_data.exec);
	if (envp != NULL)
	{
		i = 0;
		while (envp->env[i] != NULL)
		{
			free(envp->env[i]);
			i++;
		}
		free (envp->env);
		envp->env = NULL;
	}
}

void	free_list(void)
{
	t_env_list	*node_env;
	t_env_list	*tmp;

	node_env = g_data.list;
	if (node_env != NULL)
	{
		while (node_env != NULL)
		{
			if (node_env->key != NULL)
				free (node_env->key);
			if (node_env->value != NULL)
				free (node_env->value);
			tmp = node_env;
			node_env = tmp->next;
			free (tmp);
		}
		free (node_env);
	}
}

void	free_envp_list(void)
{
	free_envp();
	free_list();
}
