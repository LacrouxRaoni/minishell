#include "minishell.h"

char *print_terminal_line(char *line)
{
	char	*user;
	char	dir[1024];
	char	*aux;
	char	*aux2;


	user = getenv("USER");
	getcwd(dir, sizeof(dir));
	aux = ft_strjoin(user, "@:");
	aux2 = ft_strjoin(dir, "$");
	line = ft_strjoin(aux, aux2);
	free (aux);
	free (aux2);
	return (line);
}