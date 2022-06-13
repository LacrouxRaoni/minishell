/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:17:35 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/13 10:22:00 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_built_in(t_cmd *cmd)
{
	if (ft_str_check(cmd->word[0], "echo"))
		return (1);
	else if (ft_str_check(cmd->word[0], "pwd"))
		return (1);
	else if (ft_str_check(cmd->word[0], "env"))
		return (1);
	// else if (ft_str_check(cmd->word[0], "cd"))
	// 	return (1);
	else
		return (0);
}

void	exec_built_in(t_cmd *cmd)
{
	if (ft_str_check(cmd->word[0], "echo"))
		echo_built_in(cmd->word);
	else if (ft_str_check(cmd->word[0], "pwd"))
		pwd_built_in();
	else if (ft_str_check(cmd->word[0], "env"))
		env_built_in(cmd->word);
// 	else if (ft_str_check(cmd->word[0], "cd"))
// 		cd_built_in(cmd->word);		
}
