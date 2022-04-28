# ifndef MINISHELL_H
 #define MINISHELL_H


#define WORD
#define PIPE
#define LESS
#define DLESS
#define GLESS
#define GREAT
#define DGREAT
#define CLOBBER

typedef struct s_mns
{
	char	*line;
	char	**lexical_line;
} t_mns;


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
int		token_analysis(t_mns *data);
void	lexical_analysis(char **parsed_line, t_mns *data);

 #endif