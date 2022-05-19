/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:26:53 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/18 21:00:59 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_for_quotes(char *word)
{
	int		len;
	char	*aux;
	
	if(word[0] == '\'' || word[0] == '\"')
	{
		len = ft_strlen(word);
		aux = ft_substr(word, 1, len - 2);
	}
	else
		aux = ft_strdup(word);
	return (aux);
}

static int	exec_less(char *word)
{
	char *file_in;
	int	fd_in;

	file_in = check_for_quotes(word);
	fd_in = open(file_in, O_RDONLY);
	if (file_in < 0)
	{
		if(errno == 13)
		{	//prmission_denied
			return (0);
		}
	}
	else
		//dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	free (file_in);
}

static int	exec_great(char *word)
{
	char *file_out;
	int	fd_out;

	file_out = check_for_quotes(word);
	fd_out = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_out < 0)
	{
		if(errno == 13)
		{	//prmission_denied
			return (0);
		}
	}
	else
		//dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	free (file_out);
}


static void	exec_redirect(t_cmd **cmd)
{
	int	i;
	t_cmd *cmd_node;
	
	cmd_node = (*cmd);
	while (cmd_node != NULL)
	{
		i = 0;
		while (cmd_node->redirect[i] != NULL)
		{
			if (ft_strncmp(cmd_node->redirect[i], "<\0", 2) == 0)
			{
				i++;
				exec_less(cmd_node->redirect[i]);
				i++;
			}
			else if (ft_strncmp(cmd_node->redirect[i], ">\0", 2) == 0
				|| ft_strncmp(cmd_node->redirect[i], ">|\0", 3) == 0)
			{
				i++;
				exec_great(cmd_node->redirect[i]);
				i++;
			}
		}
		cmd_node = cmd_node->next;
	}
		
}

void	exec_cmds(t_cmd **cmd)
{
	if ((*cmd) != NULL)
	{
		if((*cmd)->here_doc[0] != NULL)
			exec_here_doc(cmd);
		if((*cmd)->redirect[0] != NULL)
			exec_redirect(cmd);
	}
}
