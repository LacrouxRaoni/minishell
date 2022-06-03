/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 20:36:06 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/03 09:16:38 by rruiz-la         ###   ########.fr       */
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
	char		*line;
	t_mns		data;

	if (argc == 1 && argv[0] != NULL)
	{
		g_data.hash[0] = create_hashtable(envp);
		g_data.hash[1] = create_hashtable(NULL);
		fulfill_hash(envp, g_data.hash[0]);
		while (1)
		{
			//imprime user+endereço na linha de comando
			line = print_terminal_line(line);
			//recebe argumento do terminal
			data.line = readline(line);
			free (line);
			if (data.line[0] != '\0')
			{
				add_history(data.line);
				if (ft_strncmp(data.line, "exit\0", 5) == 0)
				{
					//exit_shell
					free (data.line);
					free_hash_table();
					rl_clear_history();
					exit (0);
				}
				//trata linha
				data.error_num = 0;
				data.error_num = token_analysis(&data);
				if (data.error_num < 0)
				{
					//write_error
					if (data.error_num == -1)
						printf("quote is missing\n");
				}
				else
				{
					lexical_analysis(&data);
					data.error_num = syntax_analysis(data.lexical_line);
					if (data.error_num > 0)
						free_lexical_line(&data);
					else
					{
						cmd_table(&data, &g_data.cmd);
						prepare_to_exec(&g_data.cmd);
						free_cmd_table(&g_data.cmd);
					}
					free_lexical_line(&data);
				}		
				free (data.line);
			}
			else
				free (data.line);
		}
	}
	else
	{
		ft_putstr_fd("Invalid arguments\n", 1);
		return (1);
	}
	return (0);
}
