/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_d_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 21:09:16 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/23 19:22:24 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_for_assignment(t_cmd *cmd_node, int i, int *j, int *b)
{
	if (ft_strchr(cmd_node->word[i], '$') != NULL)
	{
		while (cmd_node->word[i][(*j)] != '\"')
		{
			if (cmd_node->word[i][(*j)] == '$')
			{
				(*b) = 1;
				(*j)++;
				return (0);
			}
			(*j)++;
		}
	}
	return (0);
}

static void	check_word_size(t_cmd *cmd_node, int i, int *j, int *k)
{
	while (cmd_node->word[i][(*j)])
	{
		if (cmd_node->word[i][(*j)] != '\"')
			(*k)++;
		(*j)++;
	}
	if ((*j) == 2)
		(*j) = -2;
}

static void	fulfill_dquote_line(t_cmd *cmd_node,
		char **dquote_line, int i, int b)
{
	int	j;
	int	k;

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
			(*dquote_line)[++k] = cmd_node->word[i][j];
		j++;
	}
}

static void	init_variables(int *b, int *j, int *k)
{
	(*b) = 0;
	(*j) = 0;
	(*k) = 0;
}

int	handle_d_quotes(t_cmd *cmd_node, int i)
{
	int		b;
	int		j;
	int		k;
	char	*dquote_line;

	init_variables(&b, &j, &k);
	check_for_assignment(cmd_node, i, &j, &b);
	check_word_size(cmd_node, i, &j, &k);
	if (j < 0)
		return (-2);
	if (cmd_node->word[i][j - 1] == '\"')
	{
		dquote_line = ft_calloc(k + 1, sizeof(char *));
		fulfill_dquote_line (cmd_node, &dquote_line, i, b);
	}
	else
		dquote_line = clean_quotes(cmd_node->word[i]);
	free(cmd_node->word[i]);
	cmd_node->word[i] = ft_strdup(dquote_line);
	free (dquote_line);
	if (ft_strchr(cmd_node->word[i], '$') != NULL)
		if (parse_assignment_expansion(cmd_node, i) < 0)
			return (-1);
	return (0);
}
