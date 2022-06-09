#ifndef EXECVE_H
# define EXECVE_H

typedef struct s_exec
{
	char	*path_confirmed;
	char	**path;
	int		fd[2];
} t_exec;
#endif

