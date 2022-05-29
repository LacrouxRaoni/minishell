/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_iterator.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 22:15:51 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/27 22:18:22 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_ITERATOR_H
# define CMD_ITERATOR_H

typedef struct s_cmd_iterator
{
	int	cmd_n;
	int	red_n;
	int	start;
	int	w;
	int	r;
	int	i;
}	t_iterator;

#endif
