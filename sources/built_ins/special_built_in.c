/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:57:37 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/17 02:35:10 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n_exec_special_built_in(t_cmd *cmd_node)
{
	if (ft_str_check(cmd_node->word[0], "cd"))
		cd_built_in(cmd_node->word);
	else if (ft_str_check(cmd_node->word[0], "unset"))
		unset_built_in(cmd_node->word);
	else if (ft_str_check(cmd_node->word[0], "export"))
		export_built_in(cmd_node->word);
	else if (ft_str_check(cmd_node->word[0], "exit"))
		exit_built_in(cmd_node->word);
	else
		return (1);
	return (0);
}
