/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fulfill_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:37:02 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/05 16:38:20 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_hash_pos(char *key, int size)
{
	unsigned long int	hash;
	int					i;

	hash = 5381;
	i = 0;
	while (key && key[i])
	{
		hash = (((hash << 5) + hash) + key[i]);
		i++;
	}
	return (hash % size);
}

static void	hash_add_pos(t_env_list **list, char *key, char *value)
{
	t_env_list	*node;
	t_env_list	*tmp;

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
		tmp = (*list);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

static void	hash_insert(char **key, char **value)
{
	int		index;
	t_hash	*table;

	table = g_data.hash[0];
	index = get_hash_pos((*key), table->size);
	hash_add_pos(&(table->list[index]), (*key), (*value));
	table->count++;
}

void	fulfill_hash(char **envp, t_hash *hash)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		key = extract_key(envp[i]);
		value = extract_value(envp[i]);
		hash_insert(&key, &value);
		free (key);
		free (value);
		i++;
	}
}
