/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:26:53 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/22 22:24:32 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *clean_quotes(char *content)
{
	int	i;
	int	j;
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
	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] != '\'' && content[i] != '\"')
		{
			aux[j] = content[i];
			j++;
		}
		i++;
	}
	aux[j] = '\0';
	return (aux);
}

static int	check_for_var(t_cmd *cmd_node)
{
	int		i;
	int		j;
	char	*content;

	i = 0;
	j = 0;
	if(ft_strchr(cmd_node->word[0], '=') != NULL)
	{
		if (ft_isalpha(cmd_node->word[0][0]) == 0)
			return (1);
		while (cmd_node->word[0][i])
		{
			if (cmd_node->word[0][i] == '=')
				break ;
			else if (ft_isalnum(cmd_node->word[0][i])== 0)
				return (1);
			else
				j++;
			i++;
		}
		cmd_node->var_name = ft_substr(cmd_node->word[0], 0, i);
		if (ft_strchr(cmd_node->var_name, '\'') != NULL || ft_strchr(cmd_node->var_name, '\"') != NULL)
		{
			free(cmd_node->var_name);
			return (1);
		}
		content = ft_substr(cmd_node->word[0], i + 1, ft_strlen(cmd_node->word[0]));
		if (ft_strchr(content, '\'') != NULL || ft_strchr(content, '\"') != NULL)
			 cmd_node->content = clean_quotes(content);
		printf ("%s\n", cmd_node->var_name);
		printf ("aaaaa %s\n", cmd_node->content);
		free(cmd_node->var_name);
		free(cmd_node->content);
		free(content);
	}
	return (0);
}

void	exec_words(t_cmd **cmd)
{
	t_cmd	*cmd_node;

	cmd_node = (*cmd);
	if (cmd_node != NULL)
	{
		if (cmd_node->word[0] != NULL)
			check_for_var(cmd_node);
	}
}

void	exec_cmds(t_cmd **cmd)
{
	if ((*cmd) != NULL)
	{
		if ((*cmd)->here_doc[0] != NULL)
			exec_here_doc(cmd);
		if ((*cmd)->redirect[0] != NULL)
			exec_redirect(cmd);
		if ((*cmd)->word[0] != NULL)
			exec_words(cmd);
	}
	printf("%d\n", (*cmd)->fd_in);
	printf("%d\n", (*cmd)->fd_out);
}
