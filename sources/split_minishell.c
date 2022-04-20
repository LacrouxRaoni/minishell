/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:26:32 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/04/19 21:42:31 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_n_space(t_minishell *data)
{
	int	i;
	int	n_space;

	n_space = 0;
	i = 0;
	while (data->line[i] != '\0')
	{
		if (data->line[i] == '\'')
		{
			i++;
			while (data->line[i] != '\'')
				i++;
		}
		else if (data->line[i] == '\"')
		{
			i++;
			while (data->line[i] != '\"')
				i++;
		}
		else if (data->line[i] == '<')
		{
			while (data->line[i] == '<')
				i++;
			if (data->line[i] != ' ' && data->line[i] != '\0')
				n_space++;
		}
		else if (data->line[i] == ' ')
			n_space++;
		i++;
	}
	return (n_space);
}

static int	len_subline(t_minishell *data, int start)
{
	int	i;
	int	j;

	i = start;
	j = 0;
	while (data->line[i] != '\0')
	{
		if (data->line[i] == ' ')
			break ;
		else if (data->line[i] == '\'')
		{
			//get_quotes();
			i++;
			j++;
			while (data->line[i] != '\'')
			{
				if (data->line[i] == '\0')
					return (-1);
				i++;
				j++;
			}
			i++;
			j++;
		}
		else if (data->line[i] == '\"')
		{
			i++;
			j++;
			while (data->line[i] != '\"')
			{
				if (data->line[i] == '\0')
					return (-1);
				i++;
				j++;
			}
			i++;
			j++;
		}
		else if (data->line[i] == '<')
		{
			i++;
			j++;
		}
		else
		{
			j++;
			i++;
		}
	}
	return (j);
}

static void	split_line(char **parsed_line, t_minishell *data, int n)
{
	int	i;
	int	start;
	int	len;

	start = 0;
	i = 0;
	len = 0;
	while (i <= n)
	{
		len = len_subline(data, start);
		parsed_line[i] = ft_substr(data->line, start, len);
		printf ("%s\n", parsed_line[i]);
		start = start + len + 1;
		i++;
	}
}

void	parse_line(t_minishell *data)
{
	int		n;
	char	**parsed_line;

	n = get_n_space(data);
	printf ("%d\n", n);
	parsed_line = (char **)malloc(sizeof(char *) * (n + 1));
	if (!parsed_line)
		exit (1);
	split_line(parsed_line, data, n);
}
