/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 18:52:16 by rruiz-la          #+#    #+#             */
/*   Updated: 2021/08/20 21:56:51 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*curr;
	t_list	*prev;

	if (!lst || !del)
		return ;
	curr = *lst;
	while (curr)
	{
		prev = curr;
		curr = curr->next;
		if (prev->content)
			del(prev->content);
		free(prev);
	}
	*lst = NULL;
}
