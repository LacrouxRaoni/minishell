/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:14:07 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/07 13:59:33 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_less(t_cmd *cmd_node, int i)
{
	char	*file_in;

	file_in = clean_quotes(cmd_node->redirect[i]);
	cmd_node->fd_in = open(file_in, O_RDONLY);
	if (cmd_node->fd_in < 0)
	{
		if (errno == 13)
		{	
			free (file_in);
			return (0);
		}
		else
		{
			free (file_in);
			return (1);
		}
	}
	free (file_in);
	return (0);
}

static int	exec_great(t_cmd *cmd_node, int i)
{
	char	*file_out;

	file_out = clean_quotes(cmd_node->redirect[i]);
	cmd_node->fd_out = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (cmd_node->fd_out < 0)
	{
		if (errno == 13)
		{	
			free (file_out);
			return (0);
		}
	}
	free (file_out);
	return (0);
}

static int	exec_dgreat(t_cmd *cmd_node, int i)
{
	char	*file_out;

	file_out = clean_quotes(cmd_node->redirect[i]);
	cmd_node->fd_out = open(file_out, O_WRONLY | O_APPEND, 0777);
	if (cmd_node->fd_out < 0)
	{
		free (file_out);
		return (1);
	}
	free (file_out);
	return (0);
}

static void	check_redirect_type(t_cmd *cmd_node, int *i, int *fd)
{
	if (ft_strncmp(cmd_node->redirect[(*i)], "<\0", 2) == 0)
	{
		(g_data.mns).err_num = exec_less(cmd_node, (*i) + 1);
		(*i) = (*i) + 2;
	}
	else if (ft_strncmp(cmd_node->redirect[(*i)], "<<\0", 3) == 0)
	{				
		exec_here_doc(cmd_node, (*i), fd);
		(*i) = (*i) + 2;
	}
	else if (ft_strncmp(cmd_node->redirect[(*i)], ">\0", 2) == 0)
	{
		(g_data.mns).err_num = exec_great(cmd_node, (*i) + 1);
		(*i) = (*i) + 2;
	}
	else if (ft_strncmp(cmd_node->redirect[(*i)], ">>\0", 3) == 0)
	{
		(g_data.mns).err_num = exec_dgreat(cmd_node, (*i) + 1);
		(*i) = (*i) + 2;
	}
}

void	exec_redirect(int *fd)
{
	int		i;
	t_cmd *cmd_node;

	cmd_node = g_data.cmd;
	if (cmd_node != NULL)
	{
		i = 0;
		while (cmd_node->redirect[i] != NULL)
		{
			check_redirect_type(cmd_node, &i, fd);
		}
	}	
}
