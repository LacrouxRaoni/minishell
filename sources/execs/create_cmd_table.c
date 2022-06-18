/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:23:15 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/17 17:02:51 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_cmd_table(void)
{
	t_cmd		*cmd_node;
	t_cmd		*last_node;
	t_mns		*data;

	g_data.cmd = NULL;
	data = &(g_data.mns);
	cmd_node = NULL;
	last_node = NULL;
	cmd_table(cmd_node, data, last_node);
}
