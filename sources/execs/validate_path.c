/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 10:54:23 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/18 19:49:36 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**get_path_content(void)
{
	t_env_list	*table;
	char		**path;

	table = g_data.list;
	while (table != NULL)
	{
		if (ft_strcmp(table->key, "PATH") == 0)
		{
			path = ft_split(table->value, ':');
			return (path);
		}
		table = table->next;
	}
	return (NULL);
}

void	free_path(void)
{
	int	i;

	i = -1;
	while (g_data.exec.path[++i] != NULL)
		free(g_data.exec.path[i]);
	free (g_data.exec.path);
	g_data.exec.path = NULL;
}

static int	validate_path(t_cmd *cmd_node, int i, t_exec *exec, char *aux)
{
	int		j;

	if (cmd_node->word[i][0] == '/')
	{
		exec->path_confirmed = ft_strdup(cmd_node->word[i]);
		if (access(exec->path_confirmed, F_OK) == 0)
			return (0);
		free (exec->path_confirmed);
	}
	j = -1;
	while (exec->path[++j])
	{
		aux = ft_strjoin(exec->path[j], "/");
		exec->path_confirmed = ft_strjoin(aux, cmd_node->word[i]);
		if (access(exec->path_confirmed, F_OK) == 0)
		{
			free_path();
			free (aux);
			return (0);
		}
		free (aux);
		free (exec->path_confirmed);
		exec->path_confirmed = NULL;
	}
	return (1);
}

static int	check_valid_path_cmd(t_cmd *cmd_node, int i)
{
	t_exec	*exec;
	char	*aux;

	aux = NULL;
	exec = &(g_data.exec);
	exec->path = get_path_content();
	if (validate_path(cmd_node, i, exec, aux) == 0)
		return (0);
	free_path();
	return (1);
}

int	get_path(t_cmd *cmd_node, int i)
{
	if (check_valid_path_cmd(cmd_node, i) != 0)
	{
		if (cmd_node->next == NULL)
		{
			write (1, cmd_node->word[i], ft_strlen(cmd_node->word[i]));
			write (1, ": command not found\n", 21);
			g_data.mns.exit_code = 127;
			return (1);
		}
		write (1, cmd_node->word[i], ft_strlen(cmd_node->word[i]));
		write (1, ": command not found\n", 21);
	}
	return (0);
}
