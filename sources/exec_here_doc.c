/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:58:19 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/09 13:07:28 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_line(char **limiter, int size_limiter, t_exec *exec)
{
	char	*line;

	while (1)
	{
		write (1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, (*limiter), size_limiter) == 0)
		{
			if (line[size_limiter] == '\n')
			{
				get_next_line(-1);
				free(line);
				break ;
			}
			else
				write (exec->fd[1], line, ft_strlen(line));
		}
		else
			write (exec->fd[1], line, ft_strlen(line));
		free (line);
	}
}

static void	prepare_here_doc(char **here_doc, t_exec *exec)
{
	int		pid;
	int		size_limiter;
	char	*limiter;

	limiter = clean_quotes(*here_doc);
	size_limiter = ft_strlen(limiter);
	if (pipe(exec->fd) < 0)
		exit (write(1, "Pipe error\n", ft_strlen("Pipe error\n")));
	write_line(&limiter, size_limiter, exec);
	free (limiter);
	close(exec->fd[1]);
}

void	exec_here_doc(t_cmd *cmd_node, int i)
{
	t_exec	*exec;

	exec = &(g_data.exec);
	if (ft_strncmp(cmd_node->redirect[i], "<<", 2) == 0)
	{
		i++;
		prepare_here_doc(&cmd_node->redirect[i], exec);
		cmd_node->fd_in = exec->fd[0];
		if (cmd_node->word[0] != NULL)
			dup2(cmd_node->fd_in, STDIN_FILENO);
		close(exec->fd[0]);
	}
}
