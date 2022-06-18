/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envp_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:15:11 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/18 19:49:36 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_envp_list(char **envp)
{
	int			i;
	t_env_list	*node;
	t_env_list	*last;

	i = 0;
	node = g_data.list;
	g_data.list = NULL;
	while (envp[i])
	{
		node = (t_env_list *)ft_calloc(1, sizeof(t_env_list));
		node->next = NULL;
		node->key = extract_key(envp[i]);
		node->value = extract_value(envp[i]);
		if (g_data.list == NULL)
			g_data.list = node;
		else
		{
			last = g_data.list;
			while (last->next != NULL)
				last = last->next;
			last->next = node;
		}
		i++;
	}
	g_data.exec.env = copy_env(envp);
}
