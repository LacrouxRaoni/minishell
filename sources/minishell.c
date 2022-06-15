/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 20:36:06 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/15 00:49:54 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	free_envp_list(void)
{
	t_env_list *node_env;
	t_env_list *tmp;
	t_exec	*envp;
	int	i;

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
	}
}
void	free_hash_table()
{
	t_hash *table;
	t_env_list *node;
	t_env_list	*tmp;
	int	i;
	int	h;

	h = 0;
	while (h < 2)
	{
		table = g_data.hash[h];
		i = 0;
		while (i < table->count)
		{		
			if (table->list[i])
			{
				node = table->list[i];
				while (node)
				{
					tmp = node;
					node = node->next;
					if (tmp->key != NULL)
						free (tmp->key);
					if (tmp->value != NULL)
						free (tmp->value);
					free (tmp);
				}
			}
			i++;
		}
		free (table->list);
		free (table);
		free (node);
		h++;
	}
}

t_main g_data;

int	main(int argc, char *argv[], char *envp[])
{
	// g_data = (t_main *) malloc (sizeof(t_main));
	if (argc == 1 && argv[0] != NULL)
	{
		//ou esse função
		g_data.hash[0] = create_hashtable(envp);
		g_data.hash[1] = create_hashtable(NULL);
		fulfill_hash(envp, g_data.hash[0]);
		//ou esse função - dar free
		g_data.exec.env = copy_env(envp);


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
		signal (SIGINT, kill_loop);
		while (1)
		{
			signal (SIGQUIT, SIG_IGN);
			g_data.exec.in_exec = 0;
			exec_prompt();
			if ((g_data.mns).line[0] != '\0')
			{
				signal (SIGQUIT, quit_core);
				g_data.exec.in_exec = 1;
				add_history((g_data.mns).line);
				
				//função
				if ((g_data.mns).line == 0)
				{
					if (g_data.exec.path != NULL)
						free_path();
					if (g_data.exec.path_confirmed != NULL)
					{
						free (g_data.exec.path_confirmed);
						g_data.exec.path_confirmed = NULL;
					}					
					free ((g_data.mns).line);
					free_hash_table();
					free_envp_list();
					rl_clear_history();
					clear_history();
					write (1, "exit\n", 5);
					exit (0);
				}
				if (g_data.list->d_exit == 1)
					exit (0);
				
				parsing_and_exec();
				
			}
			else
				free ((g_data.mns).line);
		}
	}
	else
	{
		ft_putstr_fd("Invalid arguments\n", 1);
		return (1);
	}
	return (0);
}
