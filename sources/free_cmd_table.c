/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 21:20:42 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/16 10:19:31 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_table(t_cmd **cmd)
{
	int		i;
	t_cmd	*temp;

	if(*cmd != NULL)
	{

		while ((*cmd)->next != NULL)
		{
			temp = (*cmd);	
			if (temp->word !=NULL)
			{
				i = -1;
				while (temp->word[++i])
					free(temp->word[i]);
				free (temp->word);
				temp->word = NULL;
			}
			if (temp->redirect !=NULL)
			{
				i = -1;
				while (temp->redirect[++i])
					free(temp->redirect[i]);
				free (temp->redirect);
				temp->redirect = NULL;
			}
			if (temp->here_doc !=NULL)
			{
				i = -1;
				while (temp->here_doc[++i])
					free(temp->here_doc[i]);
				free (temp->here_doc);
				temp->here_doc = NULL;
			}
			(*cmd) = temp->next;
			free (temp);
		}
	}
}