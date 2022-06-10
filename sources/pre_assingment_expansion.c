/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_assingment_expansion.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 21:27:12 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/10 15:34:44 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	malloc_assignment_word(t_cmd *cmd_node, int i, char ***assi_word)
{
	int	len;
	int	k;

	len = 0;
	k = 0;
	while (cmd_node->word[i][len])
	{
		if (cmd_node->word[i][len] == '$')
		{
			if (count_dollars(cmd_node, i, &len, &k) == -1)
				return (-1);
		}
		else
		{
			while (cmd_node->word[i][len] != '$'
				&& cmd_node->word[i][len] != '\0')
				len++;
			k++;
		}
	}
	*assi_word = (char **)ft_calloc(k + 1, sizeof(char *));
	if (!*assi_word)
		exit (1);
	return (len);
}

static char	*substring_word(char *word, int j, int *k)
{
	int			len;
	static int	start;
	char		*assi_word;

	if ((*k) == 0)
		start = 0;
	len = j - start;
	assi_word = ft_substr(word, start, len);
	start = j;
	return (assi_word);
}

static void	sweep_word_line(char *word, char ***assi_word, int *j, int *k)
{
	if (word[(*j)] == '$')
	{
		(*j)++;
		if (word[(*j)] == '{')
		{
			(*j) = count_keys(word, (*j));
			(*assi_word)[(*k)] = substring_word(word, (*j), &(*k));
		}
		else
		{
			while (word[(*j)] != ' '
				&& word[(*j)] != '$'
				&& word[(*j)] != '{'
				&& word[(*j)] != '}'
				&& word[(*j)] != '\0')
				(*j)++;
			(*assi_word)[(*k)] = substring_word(word, (*j), &(*k));
		}
	}
	else
	{
		while (word[(*j)] != '$' && word[(*j)] != '\0')
			(*j)++;
		(*assi_word)[(*k)] = substring_word(word, (*j), &(*k));
	}
}

static void	get_value_expansion(t_cmd *cmd_node, int i, char ***assi_word)
{
	int		j;
	char	**aux;

	j = 0;
	aux = (char **)ft_calloc(sizeof((*assi_word)), sizeof(char *));
	while ((*assi_word)[j])
	{
		if (ft_strchr((*assi_word)[j], '$') != NULL)
			aux[j] = assignment_expansion((*assi_word)[j]);
		else
			aux[j] = ft_strdup((*assi_word)[j]);
		j++;
	}	
	free(cmd_node->word[i]);
	cmd_node->word[i] = ft_str_superjoin(aux);
	free_aux_assig(&aux);
}

int	parse_assignment_expansion(t_cmd *cmd_node, int i)
{
	int		j;
	int		size;
	char	**assi_word;
	int		k;

	size = malloc_assignment_word(cmd_node, i, &assi_word);
	if (size < 0)
		return (-1);
	j = 0;
	k = 0;
	while (j < size)
	{
		sweep_word_line(cmd_node->word[i], &assi_word, &j, &k);
		k++;
	}
	assi_word[k] = NULL;
	get_value_expansion(cmd_node, i, &assi_word);
	free_aux_assig(&assi_word);
	cmd_node->expansion++;
	return (0);
}
