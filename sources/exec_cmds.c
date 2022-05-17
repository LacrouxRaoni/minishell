#include "minishell.h"

static void	write_line(t_cmd **cmd, int *fd)
{
	char	*line;
	int		limiter;

	limiter = ft_strlen((*cmd)->here_doc[1]);
	while (1)
	{
		write (1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, (*cmd)->here_doc[1], limiter) == 0)
		{
			if (line[limiter] == '\n')
			{
				free (line);
		 		get_next_line(-1);
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

static void	exec_here_doc(t_cmd **cmd)
{
	int	fd[2];

	if (pipe(fd) < 0)
		exit(write(1, "Pipe error\n", ft_strlen("Pipe error\n")));
	write_line(cmd, fd);
}

void	exec_cmds(t_cmd **cmd)
{
	int i;

	i = 0;
	if ((*cmd)->here_doc[i] != NULL)
	{
		if (ft_strncmp((*cmd)->here_doc[i], "<<\0,", ft_strlen("<<\0")) == 0)
		{
			exec_here_doc(cmd);
		}
		else
			return ;
	}
}
