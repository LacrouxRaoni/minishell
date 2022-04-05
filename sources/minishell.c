#include "minishell.h"

static char *print_terminal_line(char *line)
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

static int get_n_space(t_minishell *data)
{
	int i;
	int	n_space;

	n_space = 0;
	i = 0;
	while (data->line[i] != '\0')
	{
		if (data->line[i] == '\'')
		{
			i++;
			while (data->line[i] != '\'')
				i++;
		}
		else if (data->line[i] == '\"')
		{
			i++;
			while (data->line[i] != '\"')
				i++;
		}
		if (data->line[i] == ' ')
			n_space++;
		i++;
	}
	return (n_space);
}

static int	len_subline(t_minishell *data)
{
	int i;
	int	j;

	i = 0;
	while (data->line[i] != ' ')
	{
		j++;
		i++;
	}
	return (j);
}

static void split_line(char **parsed_line, t_minishell *data, int n)
{
	int i;
	int	start;
	int	len;

	start = 0;
	i = 0;
	while (i <= n)
	{
		len = len_subline(data);
		parsed_line[i] = ft_substr(data->line, start, len);
		printf ("teste %s\n", parsed_line[i]);
		i++;
	}
}

static void parse_line(t_minishell *data)
{
	int	n;
	char **parsed_line;

	n = get_n_space(data);
	parsed_line = (char **)malloc(sizeof(char *) * (n + 1));
	split_line(parsed_line, data, n);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;

	t_minishell data;
	(void)envp;
	if (argc != 1 || argv[0] == NULL)
	{
		perror("Invalid arguments\n");
		exit (1);
	}
	
	while (1)
	{
		//imprime user+endereço na linha de comando
		line = print_terminal_line(line);
		//recebe argumento do terminal
		data.line = readline(line);
		free (line);
		add_history(data.line);
		if (ft_strncmp(data.line, "exit\n", ft_strlen(data.line)) == 0)
		{
			free (data.line);
			return (0);
		}
		//trata linha
		parse_line(&data);
		free (data.line);
	}
	return (0);
}
