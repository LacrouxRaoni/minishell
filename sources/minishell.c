#include "minishell.h"

static void get_envp(char **envp)
{
	t_envp data_envp;
	int i;
	int len;

	len = 0;
	while (envp[len])
		len++;
	data_envp.new_envp = (char **)malloc(sizeof(char *) * len + 1);
	if (!data_envp.new_envp)
	{
		ft_putstr_fd("malloc error\n", 1);
		exit(1);
	}
	i = 0;
	while (i < len)
	{
		data_envp.new_envp[i] = envp[i];
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_minishell data;

	if (argc == 1 || argv[0] != NULL)
	{
		get_envp (envp);
		while (1)
		{
			//imprime user+endereço na linha de comando
			line = print_terminal_line(line);
			//recebe argumento do terminal
			data.line = readline(line);
			free (line);
			add_history(data.line);
			if (ft_strncmp(data.line, "exit\n", 4) == 0)
			{
				//exit_shell

				free (data.line);
				return (0);
			}
			//trata linha
			parse_line(&data);
			free (data.line);
		}
	}
	else
	{
		ft_putstr_fd("Invalid arguments\n", 1);
		return (1);
	}
	return (0);
}
