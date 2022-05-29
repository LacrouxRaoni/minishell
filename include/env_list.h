/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:26:21 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/28 12:10:37 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef ENV_LIST_H
#define ENV_LIST_H

#include "libft.h"

typedef struct s_env_list
{
	char	*key;
	char	*value;
	struct	s_env_list *next;
}	t_env_list;

typedef struct s_hash
{
	t_env_list **list;
	size_t	size;
	size_t	count;
}	t_hash;

#endif
