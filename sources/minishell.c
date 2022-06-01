/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 20:36:06 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/01 17:45:09 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_hash *create_hashtable(char **variables)
{
	t_hash	*hashtable;

	hashtable = ft_calloc(1, sizeof(t_hash));
	hashtable->size= 0;
	if (variables)
	{
		while (variables[hashtable->size])
			hashtable->size++;
	}
	if (hashtable->size > 0)
		hashtable->list = ft_calloc(hashtable->size, sizeof(t_env_list *));
	else
		hashtable->list = NULL;
	hashtable->count = 0;
	return (hashtable);
}
static char *extract_key(char  *key_line)
{
	int	i;
	char *key;

	key = '\0';		
	i = 0;
	while (key_line[i] != '=')
		i++;
	key = ft_substr(key_line, 0, i);
	return (key);
}

static char *extract_value(char *value_line)
{
	int	i;
	char	*value;	

	value = NULL;
	i = 0;
	while (value_line[i] != '=')
		i++;
	value = ft_substr(value_line, i + 1, ft_strlen(value_line) - i);
	return (value);
}

int	get_hash_pos(char *key, int size)
{
	unsigned long int	hash;
	int	i;

	hash = 5381;
	i = 0;
	while (key && key[i])
	{
		hash = (((hash << 5) + hash) + key[i]);
		i++;
	}
	return (hash % size);
}

static void hash_add_pos(t_env_list **list, char *key, char *value)
{
	t_env_list *node;
	t_env_list *tmp;

	node = (t_env_list *)malloc(sizeof(t_env_list));
	if (!node)
		exit(1);
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	if (!(*list))
		(*list) = node;
	else
	{
		int i = 0;
		tmp = (*list);
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = node;
	}		
}

static void hash_insert(char *key, char *value)
{
	int	index;
	t_hash *table;
	
	table = g_data.hash[0];


	index = get_hash_pos(key, table->size);

	hash_add_pos(&(table->list[index]), key, value);
	table->count++;
}

static void fulfill_hash(char **envp, t_hash *hash)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		key = extract_key(envp[i]);
		value = extract_value(envp[i]);
		hash_insert(key, value);		
		i++;	
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
