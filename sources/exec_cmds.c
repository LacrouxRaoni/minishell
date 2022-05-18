/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:26:53 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/17 22:47:12 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_for_quotes(t_cmd *cmd_node)
{
	int		i;
	int		len;
	char	*aux;
	
	i = 1;
	if(cmd_node->here_doc[i][0] == '\'' || cmd_node->here_doc[i][0] == '\"')
	{
		len = ft_strlen(cmd_node->here_doc[i]);
		aux = ft_substr(cmd_node->here_doc[i], 1, len - 2);
	}
	else
		aux = ft_strdup(cmd_node->here_doc[i]);
	return (aux);
}

static void	write_line(char *limiter, int size_limiter, int *fd)
{
	char	*line;
	
	while (1)
	{
		write (1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, size_limiter) == 0)
		{
			if (line[size_limiter] == '\n')
			{
				get_next_line(-1);
				free(line);
				break;
			}
			else
				write (fd[1], line, ft_strlen(line));
		}
		else
			write (fd[1], line, ft_strlen(line));
		free (line);
	}
}

static int	prepare_here_doc(t_cmd *cmd_node)
{
	int	fd[2];
	int	size_limiter;
	char *limiter;

	limiter = check_for_quotes(cmd_node);
	size_limiter = ft_strlen(limiter);
	pipe(fd);
	if (fd < 0)
		exit (write(1, "Pipe error\n", ft_strlen("Pipe error\n")));
	write_line(limiter, size_limiter, fd);
	free (limiter);
	close(fd[1]);
	return (fd[0]);
	
}

static void exec_here_doc(t_cmd **cmd)
{
	int	fd;
	t_cmd	*cmd_node;
	
	cmd_node = (*cmd);
	fd = prepare_here_doc(cmd_node);
}

void	exec_cmds(t_cmd **cmd)
{
	if ((*cmd) != NULL)
	{
		if((*cmd)->here_doc[0] != NULL)
			exec_here_doc(cmd);
	}
}
