/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 18:26:21 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/20 09:14:46 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LIST_H
# define ENV_LIST_H

// # include "libft.h"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_env_list
{
	char				*key;
	char				*value;
	int					d_exit;
	struct s_env_list	*next;
}	t_env_list;

#endif
