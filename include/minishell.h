# ifndef MINISHELL_H
 #define MINISHELL_H

typedef struct s_minishell
{
	char	*line;
} t_minishell;

/*typedef struct s_list
{
	t_minishell *start;
	char	*content; //elemento 0
	char	*next; //elemento 1
	char	*previous; //null

} t_list;
*/

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

 #endif