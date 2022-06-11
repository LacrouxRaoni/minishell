#ifndef EXECVE_H
# define EXECVE_H

typedef struct s_exec
{
	char	*path_confirmed;
	char	**path;
	int		fd[2];
	int		error;
	int		temp_fd;
	int		i;
	int		pid;
} t_exec;
#endif

