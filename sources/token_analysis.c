/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:26:32 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/08 11:06:54 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_line(char **parsed_line, t_mns *data, int n)
{
	int	i;
	int	start;
	int	len;
	int	aux;

	start = 0;
	i = 0;
	while (i <= n)
	{
		aux = 0;
		len = 0;
		len = len_subline(data, start, len, aux);
		parsed_line[i] = ft_substr(data->line, start, len);
		start = start + len;
		while (data->line[start] == ' ')
			start++;
		if (data->line[start] == '\0')
		{
			i++;
			break ;
		}
		i++;
	}
	parsed_line[i] = NULL;
	return (parsed_line);
}

static void	free_parsed_line(char **parsed_line)
{
	int	i;

	i = 0;
	while (parsed_line[i] != NULL)
	{
		free (parsed_line[i]);
		i++;
	}
	free (parsed_line);
	parsed_line = NULL;
}

int	token_analysis(t_mns *data)
{
	int		n;
	int		i;
	int		n_break;
	char	**parsed_line;

	i = 0;
	n_break = 0;
	n = get_n_break(data, i, n_break);
	if (n < 0)
		return (-1);
	parsed_line = (char **)ft_calloc(n + 1, sizeof(char *));
	if (!parsed_line)
		exit (1);
	parsed_line = split_line(parsed_line, data, n);
	lexical_analysis(parsed_line, data, n);
	free_parsed_line(parsed_line);
	return (0);
}
