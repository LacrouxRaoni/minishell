/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 20:36:06 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/24 20:24:38 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_cmd		*cmd;

	if (argc == 1 && argv[0] != NULL)
	{
		//get_envp (envp, &d_envp);
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
					//free_envp(&d_envp);
					rl_clear_history();
					exit (0);
				}
				//trata linha
				data.error_num = 0;
				data.error_num = token_analysis(&data);
				if (data.error_num < 0)
				{
					//write_error
					if (data.error_num == -1)
						printf("quote is missing\n");
				}
				else
				{
					lexical_analysis(&data);
					data.error_num = syntax_analysis(data.lexical_line);
					if (data.error_num > 0)
						free_lexical_line(&data);
					else
					{
						cmd_table(&data, &cmd);
						exec_cmds(&cmd);
						free_cmd_table(&cmd);
					}
					free_lexical_line(&data);
				}		
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
