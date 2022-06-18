/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:58:19 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/18 19:49:36 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_line(char *line, char **limiter, int size_limiter, int *fd)
{
	if (!line)
	{
		if ((g_data.mns).exit_code == 0)
			write (1, "minishell: warning: (expected delimited word)",
				ft_strlen("minishell: warning: (expected delimited word)"));
		write (1, "\n", 1);
		return (1);
	}
	if (ft_strncmp(line, (*limiter), size_limiter) == 0)
	{
		if (line[size_limiter] == '\n')
		{
			get_next_line(-1);
			free(line);
			return (1);
		}
		else
			write (fd[1], line, ft_strlen(line));
	}
	else
		write (fd[1], line, ft_strlen(line));
	free (line);
	return (0);
}

static void	write_line(char **limiter, int size_limiter, int *fd)
{
	char	*line;

	if (g_data.exec.b_hdoc > 0)
		dup2(g_data.exec.temp_fd, STDIN_FILENO);
	g_data.exec.b_hdoc = 1;
	while (1)
	{
		write (1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (check_line(line, limiter, size_limiter, fd) == 1)
			break ;
	}
}

static void	prepare_here_doc(char **here_doc, t_cmd *cmd_node)
{
	int		size_limiter;
	char	*limiter;
	int		fd[2];

	limiter = clean_quotes(*here_doc);
	size_limiter = ft_strlen(limiter);
	if (pipe(fd) < 0)
		exit (write(1, "Pipe error\n", ft_strlen("Pipe error\n")));
	g_data.exec.b_hdoc = 1;
	signal (SIGQUIT, SIG_IGN);
	write_line(&limiter, size_limiter, fd);
	free (limiter);
	close(fd[1]);
	cmd_node->fd_in = dup(fd[0]);
	close(fd[0]);
}

void	exec_here_doc(t_cmd *cmd_node, int i)
{
	(g_data.exec).in_exec = 2;
	if (ft_strncmp(cmd_node->redirect[i], "<<", 2) == 0)
	{
		i++;
		prepare_here_doc(&cmd_node->redirect[i], cmd_node);
	}
}
