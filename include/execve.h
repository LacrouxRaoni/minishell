#ifndef EXECVE_H
# define EXECVE_H

typedef struct s_exec
{
	char	*path_confirmed;
	char	**path;
	int		fd[2];
	int		error;
} t_exec;
#endif

