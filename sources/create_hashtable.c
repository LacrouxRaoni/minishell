/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_hashtable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 10:30:52 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/02 12:20:35 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hash	*create_hashtable(char **variables)
{
	t_hash	*hashtable;

	hashtable = ft_calloc(1, sizeof(t_hash));
	hashtable->size = 0;
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
