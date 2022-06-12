#ifndef EXEC_H
# define EXEC_H

typedef struct s_exec
{
	char	*path_confirmed;
	char	**path;
	int		fd[2];
	int		temp_fd;
	int		i;
	int		pid;
} t_exec;
#endif

