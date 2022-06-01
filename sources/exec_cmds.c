/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:26:53 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/01 17:51:16 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_var_n_content(t_cmd *cmd_node, int *i, int *j)
{
	if (ft_isalpha(cmd_node->word[0][0]) == 0)
		return (-1);
	while (cmd_node->word[0][(*i)])
	{
		if (cmd_node->word[0][(*i)] == '=')
			break ;
		else if (ft_isalnum(cmd_node->word[0][(*i)]) == 0)
			return (-1);
		else
			*j++;
		(*i)++;
	}
}

char	*clean_quotes(char *content)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] != '\'' && content[i] != '\"')
			j++;
		i++;
	}
	aux = (char *)ft_calloc(j + 1, sizeof(char *));
	i = -1;
	j = 0;
	while (content[++i])
	{
		if (content[i] != '\'' && content[i] != '\"')
		{
			aux[j] = content[i];
			j++;
		}
	}
	aux[j] = '\0';
	return (aux);
}

static int	check_for_var(t_cmd *cmd_node, int w)
{
	int		i;
	int		j;
	char	*content;

	i = 0;
	j = 0;
	if (ft_strchr(cmd_node->word[w], '=') != NULL)
	{
		if (split_var_n_content(cmd_node, &i, &j) == -1)
			return (1);
		cmd_node->var_name = ft_substr(cmd_node->word[w], 0, i);
		if (ft_strchr(cmd_node->var_name, '\'') != NULL
			|| ft_strchr(cmd_node->var_name, '\"') != NULL)
		{
			free(cmd_node->var_name);
			return (1);
		}
		content = ft_substr(cmd_node->word[w],
				i + 1, ft_strlen(cmd_node->word[w]));
		if (ft_strchr(content, '\'') != NULL
			|| ft_strchr(content, '\"') != NULL)
			cmd_node->content = clean_quotes(content);
		else
			cmd_node->content = ft_strdup(content);
		free(content);
		printf ("var name: %s\n", cmd_node->var_name);
		printf ("content: %s\n", cmd_node->content);
	}
	return (0);
}


void	word_expansion(t_cmd *cmd_node)
{
	int		i;

	i = 0;
	if (cmd_node != NULL)
	{
		while (cmd_node->word[i] != NULL)
		{	
			if (ft_strchr(cmd_node->word[i], '=') != NULL)
			{
				//mudar de lugar
				check_for_var(cmd_node, i);
				i++;
			}
			else if (cmd_node->word[i][0] == '~')
			{
				if (tild_expansion(cmd_node, i) == 1)
					i++;
			}
			else if ((ft_strchr(cmd_node->word[i], '\'') != NULL)
				|| (ft_strchr(cmd_node->word[i], '\"') != NULL))
			{
				quote_expansion(cmd_node, i);
				i++;
			}
			else if (ft_strchr(cmd_node->word[i], '$') != NULL)
			{
				parse_assignment_expansion(cmd_node, i);
				i++;
			}
			else
				i++;
		}
	}
}

void	prepare_to_exec(t_cmd **cmd)
{
	t_cmd *cmd_node;

	cmd_node = (*cmd);
	while (cmd_node != NULL)
	{
		if (cmd_node->word[0] != NULL)
			word_expansion(cmd_node);
		if (cmd_node->redirect[0] != NULL)
			exec_redirect(cmd, cmd_node);
		cmd_node = cmd_node->next;
	}
}
