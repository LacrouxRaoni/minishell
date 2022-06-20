/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envp_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:15:11 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/20 19:52:27 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_envp_list(void)
{
	int			i;
	t_exec		*envp;
	t_env_list	*node;
	t_env_list	*last;

	i = -1;
	envp = &(g_data.exec);
	node = g_data.list;
	g_data.list = NULL;
	while (envp->env[++i])
	{
		node = (t_env_list *)ft_calloc(1, sizeof(t_env_list));
		node->next = NULL;
		node->key = extract_key(envp->env[i]);
		node->value = extract_value(envp->env[i]);
		if (g_data.list == NULL)
			g_data.list = node;
		else
		{
			last = g_data.list;
			while (last->next != NULL)
				last = last->next;
			last->next = node;
		}
	}	
}
