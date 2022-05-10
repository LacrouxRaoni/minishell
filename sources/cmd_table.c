#include "minishell.h"

void cmd_table(char **parsed_line, t_mns *data, t_cmd *cmd)
{
	//definir tam cmd
	int i;
	int cmd_n;
	int	red_n;
	int	hdoc_n;

	red_n = 0;
	cmd_n = 0;
	hdoc_n = 0;
	i = 0;
	while (data->lexical_line[i])
	{
		if (ft_strncmp(data->lexical_line[i], "WORD\0", 5) != 0)
		{
			if (ft_strncmp(data->lexical_line[i], "PIPE", 4) == 0)
				red_n++;
			else if ((ft_strncmp(data->lexical_line[i], "DLESS", 5) == 0))
			{
				i = i + 1;
				hdoc_n = hdoc_n + 2;
			}
			else
			{
				i = i + 1;
				red_n = red_n + 2;
			}
		}
		else
			cmd_n++;
		i++;	
	}
	//alocar mem
	cmd->cmd = (char **)ft_calloc(cmd_n + 1, sizeof(char *));
	cmd->redirect = (char **)ft_calloc(red_n + 1, sizeof(char *));
	cmd->here_doc = (char **)ft_calloc(hdoc_n + 1, sizeof(char *));
	//parsear linha

	int w;
	int h;
	int r;

	i = 0;
	w = 0;
	h = 0;
	r = 0;
	while (data->lexical_line[i])
	{
		if (ft_strncmp(data->lexical_line[i], "WORD\0", 5) != 0)
		{
			if (ft_strncmp(data->lexical_line[i], "PIPE", 4) == 0)
			{
				cmd->redirect[r] = ft_strdup(parsed_line[i]);
				printf ("%s\n", cmd->redirect[r]);
				break ;
			}
			else if (ft_strncmp(data->lexical_line[i], "DLESS", 5) == 0)
			{
				cmd->here_doc[h] = ft_strdup(parsed_line[i]);
				printf ("%s " ,cmd->here_doc[h]);
				i++;
				h++;
				cmd->here_doc[h] = ft_strdup(parsed_line[i]);
				printf ("%s\n" ,cmd->here_doc[h]);
			}
			else
			{
				cmd->redirect[r] = ft_strdup(parsed_line[i]);
				printf ("%s " ,cmd->redirect[r]);
				i++;
				r++;
				cmd->redirect[r] = ft_strdup(parsed_line[i]);
				printf ("%s\n" ,cmd->redirect[r]);
			}
		}
		else
		{
			cmd->cmd[w] = ft_strdup(parsed_line[i]);
			printf ("%s\n" ,cmd->cmd[w]);
			w++;
		}

		i++;
	}
	
}
