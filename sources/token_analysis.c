/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:26:32 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/13 22:39:05 by rruiz-la         ###   ########.fr       */
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
		while (data->line[start] == ' ')
			start++;
		if (data->line[start] == '\0')
		{
			i++;
			break ;
		}
		len = len_subline(data, start, len, aux);
		parsed_line[i] = ft_substr(data->line, start, len);
		start = start + len;
		i++;
	}
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

static void	free_lexical_line(t_mns *data)
{
	int	i;

	i = -1;
	while (data->lexical_line[++i])
		free (data->lexical_line[i]);
	free(data->lexical_line);
	data->lexical_line = NULL;
}

static char	**malloc_parsed_line(int n)
{
	char	**parsed_line;

	parsed_line = (char **)ft_calloc(n + 1, sizeof(char *));
	if (!parsed_line)
		exit (1);
	return (parsed_line);
}

int	token_analysis(t_mns *data, t_cmd **cmd)
{
	int		n;
	int		i;
	char	**parsed_line;

	i = 0;
	n = get_n_break(data, i);
	if (n < 0)
		return (-1);
	parsed_line = malloc_parsed_line(n);
	parsed_line = split_line(parsed_line, data, n);
	if (parsed_line[0] == 0)
	{
		free_parsed_line(parsed_line);
		return (0);
	}
	if (lexical_analysis(parsed_line, data, n) > 0)
	{
		free_lexical_line(data);
		free_parsed_line(parsed_line);
		return (2);
	}
	cmd_table(parsed_line, data, cmd);
	free_lexical_line(data);
	free_parsed_line(parsed_line);
	return (0);
}
