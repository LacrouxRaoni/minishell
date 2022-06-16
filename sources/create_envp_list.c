/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envp_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 10:15:11 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/15 21:39:10 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_envp_list(char **envp)
{
	int	i = 0;
	t_env_list	*node;
	t_env_list	*last;
	
	node = g_data.list;
	g_data.list = NULL;
	while(envp[i])
	{
		node = (t_env_list *)malloc(sizeof(t_env_list));
		node->next = NULL;
		node->key = extract_key(envp[i]);
		node->value = extract_value(envp[i]);
		if (g_data.list == NULL)
			g_data.list = node;
		else
		{
			last = g_data.list;
			while(last->next != NULL)
				last = last->next;
			last->next = node;
		}
		i++;
	}
	g_data.exec.env = copy_env(envp);
}
