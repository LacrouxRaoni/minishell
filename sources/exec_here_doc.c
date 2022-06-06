/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:58:19 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/06 14:58:05 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_line(char **limiter, int size_limiter, int *fd)
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
				write (fd[1], line, ft_strlen(line));
		}
		else
			write (fd[1], line, ft_strlen(line));
		free (line);
	}
}

static int	prepare_here_doc(char **here_doc)
{
	int		pid;
	int		fd[2];
	int		size_limiter;
	char	*limiter;

	limiter = clean_quotes(*here_doc);
	size_limiter = ft_strlen(limiter);
	if (pipe(fd) < 0)
		exit (write(1, "Pipe error\n", ft_strlen("Pipe error\n")));
	write_line(&limiter, size_limiter, fd);
	free (limiter);
	close(fd[1]);
	return (fd[0]);
}

void	exec_here_doc(t_cmd *cmd_node, int i)
{
	int		fd;

	if (ft_strncmp(cmd_node->redirect[i], "<<", 2) == 0)
	{
		i++;
		fd = prepare_here_doc(&cmd_node->redirect[i]);
	}
	cmd_node->fd_in = fd;
	close (fd);
}
