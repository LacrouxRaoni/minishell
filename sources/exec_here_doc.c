/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:58:19 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/11 12:30:03 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_line(char **limiter, int size_limiter, int *fd)
{
	char	*line;

	close (fd[0]);
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
	close (fd[1]);
}

static int	prepare_here_doc(char **here_doc, t_cmd *cmd_node)
{
	int		size_limiter;
	char	*limiter;
	int		fd[2];
	int		pid;

	limiter = clean_quotes(*here_doc);
	size_limiter = ft_strlen(limiter);
	if (pipe(fd) < 0)
		exit (write(1, "Pipe error\n", ft_strlen("Pipe error\n")));
	pid = fork();
	if (pid < 0)
		exit (write (1, "Fork error\n", 14));
	if (pid == 0)
	{
		write_line(&limiter, size_limiter, fd);
		free_cmd_table();
		free_envp_list();
		free_hash_table();
		free_lexical_line();
		rl_clear_history();
		free (limiter);
		exit (0);
	}
	waitpid (pid, NULL, 0);
	free (limiter);
	close(fd[1]);
	cmd_node->fd_in = dup(fd[0]);
	close(fd[0]);
}

void	exec_here_doc(t_cmd *cmd_node, int i)
{


	if (ft_strncmp(cmd_node->redirect[i], "<<", 2) == 0)
	{
		i++;
		prepare_here_doc(&cmd_node->redirect[i], cmd_node);
	}
}
