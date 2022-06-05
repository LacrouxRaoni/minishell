/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:26:32 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/05 12:36:14 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_line(char **parsed_line, t_mns *data)
{
	int	i;
	int	start;
	int	len;
	int	aux;

	start = 0;
	i = 0;
	while (i <= data->n)
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

static void	free_parsed_line(char **line)
{
	int	i;

	i = 0;
	while (line[i] != NULL)
	{
		free (line[i]);
		i++;
	}
	free (line);
	line = NULL;
}

static char	**malloc_parsed_line(int n)
{
	char	**parsed_line;

	parsed_line = (char **)ft_calloc(n + 1, sizeof(char *));
	if (!parsed_line)
		exit (1);
	return (parsed_line);
}

static void	malloc_data_parsed_line(t_mns *data, char **parsed_line)
{
	int	i;

	data->parsed_line
		= (char **)ft_calloc(data->n + 1, sizeof(parsed_line));
	if (!data->parsed_line)
		exit (1);
	i = -1;
	while (parsed_line[++i])
		data->parsed_line[i] = ft_strdup(parsed_line[i]);
	free_parsed_line(parsed_line);
}

int	token_analysis(void)
{
	int		i;
	char	**parsed_line;
	t_mns	*data;

	data = &(g_data.mns);
	i = 0;
	data->n = get_n_break(data, i);
	if (data->n < 0)
		return (-1);
	parsed_line = malloc_parsed_line(data->n);
	parsed_line = split_line(parsed_line, data);
	if (parsed_line[0] == 0)
	{
		free_parsed_line(parsed_line);
		return (-2);
	}
	else
		malloc_data_parsed_line(data, parsed_line);
	return (0);
}
