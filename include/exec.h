#ifndef EXEC_H
# define EXEC_H

typedef struct s_exec
{
	char	**env;
	char	*path_confirmed;
	char	**path;
	int		fd[2];
	int		temp_fd;
	int		b_hdoc;
	int		pid;
	int		in_exec;
} t_exec;
#endif

