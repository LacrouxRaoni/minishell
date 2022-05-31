/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:26:53 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/30 22:49:58 by rruiz-la         ###   ########.fr       */
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




static int 	expand_key_value(char **dollar)
{
	int index;
	int r;
	t_hash *h_list;
	
	r = 0;
	while (r < 2)
	{
		if (g_data.hash[r]->size == 0)
		{
			free (*dollar);
			*dollar = ft_strdup("");
			return (1);
		}
		index = get_hash_pos(*dollar, g_data.hash[r]->size);

		h_list = g_data.hash[r];
		while (h_list->list[index])
		{
			if (ft_strcmp(h_list->list[index]->key, *dollar) > 0)
				h_list->list[index] = h_list->list[index]->next;
			else
			{
				free (*dollar);
				*dollar = ft_strdup(h_list->list[index]->value);
				r = 2;
				return (0);
			}	
		}
		r++;
	}		
}


void	assignment_expansion(char *assi_word)
{
	int		j;
	int		b;
	char	*dollar;
	
	b = 0;
	j = 0;
	dollar = NULL;
	if (assi_word[j] == '$')
	{
		if (assi_word[j + 1] == '{')
		{
			while (assi_word[j] != '}')
			{
				if (assi_word[j] == '\0')
				{
					b = 1;
					break ;
				}
				j++;
			}
			if (b == 0)
				dollar = ft_substr(assi_word, 2, j - 2);
		}	
		else
			dollar = ft_substr(assi_word,
					1, ft_strlen(assi_word));
	}
	printf("dolar %s\n", dollar);
	expand_key_value(&dollar);
	printf("new dolar %s\n", dollar);
	
	
	
	if (b == 0)
		free (dollar);
}


void parse_assignment_expansion(t_cmd *cmd_node, int i)
{
	int	j;
	int	k;
	int start;
	int	end;
	int	len;
	int	n_break;
	char	**assi_word;

	j = 0;
	k = 0;
	start = 0;
	end = 0;
	n_break = 0;
	while (cmd_node->word[i][j])
	{
		if (cmd_node->word[i][j] == '$')
			k++;
		j++;
	}
	len = j;
	assi_word = (char **)ft_calloc(k + 1, sizeof(char *));
	n_break = k;
	j = 0;
	k = 0;
	while (j <= len)
	{
		if (cmd_node->word[i][j] == '$' || cmd_node->word[i][j - 1] == '}' || cmd_node->word[i][j] == '\0')
		{
			if (cmd_node->word[i][j] == '\0' && n_break == 1)
				break ;
			end = j - start;
			if (end == 0)
				end = len;
			assi_word[k] = ft_substr(cmd_node->word[i], start, end);
			printf ("%s\n", assi_word[k]);
			k++;
			start = j;
		}
		j++;
	}
	assi_word[k] = NULL;
	j = 0;
	while (assi_word[j])
	{
		if (ft_strchr(assi_word[j], '$') != NULL)
			assignment_expansion(assi_word[j]);
		j++;
	}
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
				parse_assignmet_expansion(cmd_node, i);
				i++;
			}
			else
				i++;
		}
	}
}

void	exec_cmds(t_cmd **cmd)
{
	t_cmd *cmd_node;

	cmd_node = (*cmd);
	while (cmd_node != NULL)
	{
		if (cmd_node->redirect[0] != NULL)
			exec_redirect(cmd, cmd_node);
		if (cmd_node->word[0] != NULL)
			word_expansion(cmd_node);
		printf("%d\n", cmd_node->fd_in);
		printf("%d\n", cmd_node->fd_out);
		cmd_node = cmd_node->next;
	}
}
