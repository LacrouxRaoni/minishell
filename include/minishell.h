# ifndef MINISHELL_H
 #define MINISHELL_H

typedef struct s_minishell
{
	char	*line;
} t_minishell;


 #include "env_list.h"
 #include <stdio.h>
 #include <readline/readline.h>
 #include <readline/history.h>
 #include <unistd.h>
 #include <stdlib.h>
 #include <fcntl.h>
 #include <sys/types.h>
 #include <sys/wait.h>
 #include <errno.h>
 #include "./libft.h"


char	*print_terminal_line(char *line);
void	parse_line(t_minishell *data);

 #endif