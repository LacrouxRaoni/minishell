/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 20:36:06 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/11 17:00:39 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	free_envp_list(void)
{
	t_env_list *env;
	t_env_list *tmp;
	int	i;

	env = &(g_data.list);
	while (env != NULL)
	{
		i = 0;
		tmp = env->next;
		if (env->key != NULL)	
			free (env->key);
		if (env->value != NULL)
			free (env->value);
		if (env->env[i] != NULL)
		{
			while (env->env[i] != NULL)
			{
				free(env->env[i]);
				i++;
			}
			free (env->env);
			env->env = NULL;
		}
		free(tmp);
		env = env->next;
	}
	free (env);
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
		g_data.list.env = cp_first_env(envp);

		while (1)
		{
			exec_prompt();
			if ((g_data.mns).line[0] != '\0')
			{
				add_history((g_data.mns).line);
				
				//função
				if (ft_strncmp((g_data.mns).line, "exit\0", 5) == 0)
				{
					free ((g_data.mns).line);
					free_hash_table();
					free_envp_list();
					rl_clear_history();
					clear_history();
					exit (0);
				};

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
