/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:23:15 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/18 19:49:36 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
