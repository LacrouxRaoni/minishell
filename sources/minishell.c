#include "minishell.h"

static void get_envp(char **envp, t_envp *data_envp)
{
	int i;
	int len;

	len = 0;
	while (envp[len] != NULL)
		len++;
	data_envp->new_envp = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!data_envp->new_envp)
	{
		ft_putstr_fd("malloc error\n", 1);
		exit(1);
	}
	i = -1;
	while (++i < len)
		data_envp->new_envp[i] = ft_strdup(envp[i]);
}

static void free_envp(t_envp *d_envp)
{
	int i;

	if (d_envp->new_envp != NULL)
	{
		i = 0;
		while (d_envp->new_envp[i] != NULL)
		{
			free (d_envp->new_envp[i]);
			i++;
		}
		free (d_envp->new_envp);
		d_envp->new_envp = NULL;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_mns		data;
	t_envp		d_envp;
	t_cmd		cmd;

	if (argc == 1 && argv[0] != NULL)
	{
		get_envp (envp, &d_envp);
		while (1)
		{
			//imprime user+endereço na linha de comando
			line = print_terminal_line(line);
			//recebe argumento do terminal
			data.line = readline(line);
			free (line);
			if (data.line[0] != '\0')
			{
				add_history(data.line);
				if (ft_strncmp(data.line, "exit\0", 5) == 0)
				{
					//exit_shell

					free (data.line);
					free_envp(&d_envp);
					exit (0);
				}
				//trata linha
				if (token_analysis(&data, &cmd) == -1)
					ft_putstr_fd("quote is missing\n", 1); //lembrar de tratar erro e frees e código de saída
				free (data.line);			
			}
			else
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
