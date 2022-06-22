/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:53:28 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/22 14:59:20 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_path(void)
{
	int	i;

	i = -1;
	while (g_data.exec.path[++i] != NULL)
		free(g_data.exec.path[i]);
	free (g_data.exec.path);
	g_data.exec.path = NULL;
}
