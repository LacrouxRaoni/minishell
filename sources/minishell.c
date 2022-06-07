/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 20:36:06 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/07 13:33:35 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (argc == 1 && argv[0] != NULL)
	{
		//função
		g_data.hash[0] = create_hashtable(envp);
		g_data.hash[1] = create_hashtable(NULL);
		fulfill_hash(envp, g_data.hash[0]);
		

		while (1)
		{
			//função
			print_terminal_line();
			(g_data.mns).line = readline((g_data.mns).line_cmd);
			free ((g_data.mns).line_cmd);
			
			if ((g_data.mns).line[0] != '\0')
			{
				add_history((g_data.mns).line);
				//função
				if (ft_strncmp((g_data.mns).line, "exit\0", 5) == 0)
				{
					free ((g_data.mns).line);
					free_hash_table();
					rl_clear_history();
					exit (0);
				}
				//função
				if (token_analysis() < 0)
				{
					if ((g_data.mns).err_num == -1)
						printf("quote is missing\n");
				}
				else
				{
					//função
					lexical_analysis();
					if (syntax_analysis() > 0)
					{
						(g_data.mns).err_num = 2;
						//retorna 1
					}
					else
					{
						//função
						cmd_table();
						if (word_expansion() < 0)
						{
							(g_data.mns).err_num = 1;
							free_cmd_table();
						}
						else
						{
							//exec_cmd
							prepare_to_exec();
							free_cmd_table();
						}
						//retorna 0
					}
					free_lexical_line();
				}		
				free ((g_data.mns).line);
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
