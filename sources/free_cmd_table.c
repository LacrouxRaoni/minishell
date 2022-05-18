/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 21:20:42 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/17 17:39:24 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_table(t_cmd **cmd)
{
	int		i;
	t_cmd	*temp;

	if ((*cmd) != NULL)
	{
		while ((*cmd) != NULL)
		{
			if ((*cmd)->word !=NULL)
			{
				i = -1;
				while ((*cmd)->word[++i])
					free((*cmd)->word[i]);
				free ((*cmd)->word);
				(*cmd)->word = NULL;
			}
			if ((*cmd)->redirect !=NULL)
			{
				i = -1;
				while ((*cmd)->redirect[++i])
					free((*cmd)->redirect[i]);
				free ((*cmd)->redirect);
				(*cmd)->redirect = NULL;
			}
			if ((*cmd)->here_doc !=NULL)
			{
				i = -1;
				while ((*cmd)->here_doc[++i])
					free((*cmd)->here_doc[i]);
				free ((*cmd)->here_doc);
				(*cmd)->here_doc = NULL;
			}
			temp = (*cmd);
			(*cmd) = temp->next;
			free (temp);
		}
		
	}
}