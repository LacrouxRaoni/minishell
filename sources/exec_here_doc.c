/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 11:58:19 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/18 11:59:10 by rruiz-la         ###   ########.fr       */
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

static void	write_line(char *limiter, int size_limiter, int *fd)
{
	char	*line;
	
	close (fd[0]);
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
	close(fd[1]);
	exit(0);
}

static int	prepare_here_doc(char *here_doc, int wstatus)
{
	int	fd[2];
	int	pid;
	int	size_limiter;
	char *limiter;

	limiter = check_for_quotes(here_doc);
	size_limiter = ft_strlen(limiter);
	if (pipe(fd) < 0)
		exit (write(1, "Pipe error\n", ft_strlen("Pipe error\n")));
	pid = fork();
	if (pid < 0)
		exit (write(1, "Fork error\n", ft_strlen("Fork error\n")));
	if (pid == 0)
		write_line(limiter, size_limiter, fd);
	waitpid(pid, &wstatus, 0);
	if (!WIFSIGNALED(wstatus));
		printf("linha 76 hdoc %d\n", wstatus);
	free (limiter);
	close(fd[1]);
	return (fd[0]);
	
}

void exec_here_doc(t_cmd **cmd)
{
	int		i;
	int		fd;
	int		wstatus;
	t_cmd	*cmd_node;
	
	cmd_node = (*cmd);
	while (cmd_node != NULL)
	{
		i = 0;
		while (cmd_node->here_doc[i] != NULL)
		{
			i++;
			fd = prepare_here_doc(cmd_node->here_doc[i], wstatus);
			i++;
		}
		cmd_node = cmd_node->next;
		if (i < 1)
		{
			if (cmd_node == NULL)
				//dup2(fd, STDIN_FILENO);
			close (fd);
		}
	}
}
