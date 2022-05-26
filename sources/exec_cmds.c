/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:26:53 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/26 18:51:23 by rruiz-la         ###   ########.fr       */
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

static char	*clean_quotes(char *content)
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

static int	check_for_var(t_cmd *cmd_node, int *w)
{
	int		i;
	int		j;
	char	*content;

	i = 0;
	j = 0;
	if (ft_strchr(cmd_node->word[(*w)], '=') != NULL)
	{
		if (split_var_n_content(cmd_node, &i, &j) == -1)
			return (1);
		cmd_node->var_name = ft_substr(cmd_node->word[(*w)], 0, i);
		if (ft_strchr(cmd_node->var_name, '\'') != NULL
			|| ft_strchr(cmd_node->var_name, '\"') != NULL)
		{
			free(cmd_node->var_name);
			return (1);
		}
		content = ft_substr(cmd_node->word[(*w)],
				i + 1, ft_strlen(cmd_node->word[(*w)]));
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










static void tild_expansion(t_cmd *cmd_node, int i)
{
	char *line;
	
	line = '\0';
	if(cmd_node->word[i][0] == '~')	
	{
		if (cmd_node->word[i][1] == '\0')
			line = getenv("HOME");
		else if ((ft_strchr(cmd_node->word[i], '\'') == NULL) || ft_strchr(cmd_node->word[i], '\"') == NULL)
		{
			if (ft_strcmp(cmd_node->word[i], "~+\0") == 0)
					line = getenv("PWD");
			else if (ft_strcmp(cmd_node->word[i], "~-\0") == 0)
				line = getenv("OLDPWD");
			else if (ft_strchr(cmd_node->word[i], '/') != NULL)
			{	
				if (ft_strcmp(cmd_node->word[i], "~/\0") == 0)
					line = getenv("HOME");
			}
		}
		printf ("tilde %s\n", line);
	}	
}




























static void handle_s_quote(t_cmd *cmd_node, int i)
{
	int	b;
	int	j;
	int	k;
	char	*quote_line;
	
	j = 0;
	k = 0;
	b = 0;
	if (ft_strchr(cmd_node->word[i], '$') != NULL)
	{
		while(cmd_node->word[i][j] != '\'')
		{
			if (cmd_node->word[i][j] == '$')
			{
				b = 1;
				j++;
			 	break ;
			}
			j++;
		}
	}
	while (cmd_node->word[i][j])
	{
		if (cmd_node->word[i][j] != '\'')
			k++;
		j++;
	}
	quote_line = ft_calloc(k + 1, sizeof(char *));
	j = 0;
	k = -1;
	while (cmd_node->word[i][j])
	{
		if (b > 0)
		{
			while (cmd_node->word[i][j] != '\'')
				j++;
			b = 0;
		}
		if (cmd_node->word[i][j] != '\'')
			quote_line[++k] = cmd_node->word[i][j];
		j++;
	}
	printf ("quote %s\n", quote_line);
	free (quote_line);
}


static void	handle_d_quotes(t_cmd *cmd_node, int i)
{
	int	b;
	int	j;
	int	k;
	char	*dquote_line;
	
	b = 0;
	j = 0;
	k = 0;
	if (ft_strchr(cmd_node->word[i], '$') != NULL)
	{
		while(cmd_node->word[i][j] != '\"')
		{
			if (cmd_node->word[i][j] == '$')
			{
				b = 1;
				j++;
			 	break ;
			}
			j++;
		}
	}
	while (cmd_node->word[i][j])
	{
		if (cmd_node->word[i][j] != '\'')
			k++;
		j++;
	}
	dquote_line = ft_calloc(k + 1, sizeof(char *));
	j = 0;
	k = -1;
	while (cmd_node->word[i][j])
	{
		if (b > 0)
		{
			while (cmd_node->word[i][j] != '\"')
				j++;
			b = 0;
		}
		if (cmd_node->word[i][j] != '\"')
			dquote_line[++k] = cmd_node->word[i][j];
		j++;
	}
	printf ("dquote %s\n", dquote_line);
	if (ft_strchr(dquote_line, '$') != NULL)
		printf ("expand $\n");
	free (dquote_line);
}

static void	quote_expansion(t_cmd *cmd_node, int i)
{
	int	j;

	j = 0;
	while (cmd_node->word[i][j])
	{
		if (cmd_node->word[i][j] == '\'')
		{
			handle_s_quote(cmd_node, i);
			break ;
		}
		else if (cmd_node->word[i][j] == '\"')
		{
			handle_d_quotes(cmd_node, i);
			break ;
		}
		j++;
	}
}








































static void	assignment_expansion(t_cmd *cmd_node, int i)
{
	int		j;
	char	*dollar;
	
	j = 0;
	if (cmd_node->word[i][j] == '$')
			dollar = ft_strdup(cmd_node->word[i]);
	printf ("dollar %s\n", dollar);
	free (dollar);
}



void	word_expansion(t_cmd **cmd)
{
	int		i;
	t_cmd	*cmd_node;

	i = 0;
	cmd_node = (*cmd);
	while (cmd_node != NULL)
	{
		while (cmd_node->word[i] != NULL)
		{
			if (ft_strchr(cmd_node->word[i], '=') != NULL)
				check_for_var(cmd_node, &i);
			else if(cmd_node->word[i][0] == '~')
				tild_expansion(cmd_node, i);
			else if ((ft_strchr(cmd_node->word[i], '\'') != NULL) || (ft_strchr(cmd_node->word[i], '\"') != NULL))
				quote_expansion(cmd_node, i);
			else if (cmd_node->word[i][0] == '$')
				assignment_expansion(cmd_node, i);
			i++;
		}
		cmd_node = cmd_node->next;
	}
}

void	exec_cmds(t_cmd **cmd)
{
	if ((*cmd) != NULL)
	{
		if ((*cmd)->redirect[0] != NULL)
			exec_redirect(cmd);
		if ((*cmd)->word[0] != NULL)
			word_expansion(cmd);
	}
	printf("%d\n", (*cmd)->fd_in);
	printf("%d\n", (*cmd)->fd_out);
}
