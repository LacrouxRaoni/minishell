/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:58:19 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/21 13:35:47 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_for_quotes(char **word)
{
	int		len;
	char	*aux;

	if ((*word)[0] == '\'' || (*word)[0] == '\"')
	{
		len = ft_strlen(*word);
		aux = ft_substr(*word, 1, len - 2);
	}
	else
		aux = ft_strdup(*word);
	return (aux);
}

static void	write_line(char **limiter, int size_limiter, int *fd)
{
	char	*line;

	close(fd[0]);
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
				write (fd[1], line, ft_strlen(line));
		}
		else
			write (fd[1], line, ft_strlen(line));
		free (line);
	}
	close(fd[1]);
}

static int	prepare_here_doc(char **here_doc, t_cmd **cmd)
{
	int		pid;
	int		fd[2];
	int		size_limiter;
	char	*limiter;

	limiter = check_for_quotes(here_doc);
	size_limiter = ft_strlen(limiter);
	if (pipe(fd) < 0)
		exit (write(1, "Pipe error\n", ft_strlen("Pipe error\n")));
	pid = fork();
	if (pid < 0)
		exit (write(1, "Fork error\n", ft_strlen("Fork error\n")));
	if (pid == 0)
	{
		write_line(&limiter, size_limiter, fd);
		free (limiter);
		free_cmd_table(cmd);
		exit(0);
	}
	waitpid(pid, NULL, 0);
	free (limiter);
	close(fd[1]);
	return (fd[0]);
}

void	exec_here_doc(t_cmd **cmd)
{
	int		i;
	int		fd;
	t_cmd	*cmd_node;

	cmd_node = (*cmd);
	while (cmd_node != NULL)
	{
		i = -1;
		while (cmd_node->here_doc[++i] != NULL)
		{
			if (ft_strncmp(cmd_node->here_doc[i], "<<", 2) != 0)
				fd = prepare_here_doc(&cmd_node->here_doc[i], cmd);
		}
		cmd_node->fd_in = fd;
		cmd_node = cmd_node->next;
		close (fd);
	}
}
