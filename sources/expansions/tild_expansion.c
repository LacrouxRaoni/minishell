/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tild_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:59:43 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/19 20:07:33 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_tild_type(t_cmd *cmd_node, int i, char **line, char **tmp)
{
	if (ft_strcmp(cmd_node->word[i], "~+\0") == 0)
		(*line) = find_env("PWD");
	else if (ft_strcmp(cmd_node->word[i], "~-\0") == 0)
	{
		(*line) = find_env("OLDPWD");
		if (!(*line))
			return (1);
	}
	else if (ft_strchr(cmd_node->word[i], '/') != NULL)
	{	
		if (ft_strcmp(cmd_node->word[i], "~/\0") == 0)
			(*line) = find_env("HOME");
		else
		{
			(*line) = find_env("HOME");
			(*tmp) = ft_substr(cmd_node->word[i], 1,
					ft_strlen(cmd_node->word[i]));
		}
	}
	else
		return (1);
	return (0);
}

static void	include_tild_in_cmd_table(t_cmd *cmd_node,
		int i, char **line, char **tmp)
{
	free (cmd_node->word[i]);
	if ((*tmp))
	{
		cmd_node->word[i] = ft_strjoin((*line), (*tmp));
		free ((*tmp));
	}
	else
		cmd_node->word[i] = ft_strdup((*line));
}

int	tild_expansion(t_cmd *cmd_node, int i)
{
	char	*line;
	char	*tmp;

	line = NULL;
	tmp = NULL;
	if (cmd_node->word[i][0] == '~')
	{
		if (cmd_node->word[i][1] == '\0')
		{
			line = find_env("HOME");
			free (cmd_node->word[i]);
			cmd_node->word[i] = ft_strdup(line);
		}
		else if ((ft_strchr(cmd_node->word[i], '\'') == NULL)
			|| ft_strchr(cmd_node->word[i], '\"') == NULL)
		{
			if (check_tild_type(cmd_node, i, &line, &tmp) == 1)
				return (1);
			else
				include_tild_in_cmd_table(cmd_node, i, &line, &tmp);
		}
	}
	return (0);
}
