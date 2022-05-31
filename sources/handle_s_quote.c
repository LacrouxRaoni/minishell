/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_s_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:50:29 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/30 11:49:16 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_for_assignment(t_cmd *cmd_node, int i, int *j, int *b)
{
	if (ft_strchr(cmd_node->word[i], '$') != NULL)
	{
		while (cmd_node->word[i][(*j)] != '\'')
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
		if (cmd_node->word[i][(*j)] != '\'')
			(*k)++;
		(*j)++;
	}
}

static void	fulfill_quote_line(t_cmd *cmd_node,
		char **quote_line, int i, int b)
{
	int	j;
	int	k;

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
			(*quote_line)[++k] = cmd_node->word[i][j];
		j++;
	}
}

void	handle_s_quote(t_cmd *cmd_node, int i)
{
	int		b;
	int		j;
	int		k;
	char	*quote_line;

	j = 0;
	k = 0;
	b = 0;
	check_for_assignment(cmd_node, i, &j, &b);
	check_word_size(cmd_node, i, &j, &k);
	if (cmd_node->word[i][j - 1] == '\'')
	{
		quote_line = ft_calloc(k + 1, sizeof(char *));
		fulfill_quote_line (cmd_node, &quote_line, i, b);
	}
	else
		quote_line = clean_quotes(cmd_node->word[i]);
	free(cmd_node->word[i]);
	cmd_node->word[i] = ft_strdup(quote_line);
	free (quote_line);
}
