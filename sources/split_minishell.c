/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:26:32 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/04/21 23:22:27 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_tokens(t_minishell *data, int i)
{
	if (data->line[i] == '<')
	{
		if (data->line[i + 1] == '<')
			i++;
		if (data->line[i + 1] == '<')
			i++;
		i++;
	}
	else if (data->line[i] == '>')
	{
		if (data->line[i + 1] == '>')
			i++;
		else if (data->line[i + 1] == '|')
			i++;
		i++;
	}
	else if (data->line[i] == '|')
	{
		i++;
	}
	return (i);
}

static int count_quotes(t_minishell *data, int i)
{
	if (data->line[i] == '\'')
	{
		i++;
		while (data->line[i] != '\'')
			i++;
		i++;
	}
	if (data->line[i] == '\"')
	{
		i++;
		while (data->line[i] != '\"')
			i++;
		i++;
	}
	return (i);
}

static int	get_n_break(t_minishell *data)
{
	int	i;
	int	n_break;

	n_break = 0;
	i = 0;
	while (data->line[i] != '\0')
	{
		while (data->line[i] == ' ' && data->line[i] != '\0')
			i++;
		if (ft_strchr("><|" , data->line[i]) != NULL)
			i = count_tokens(data, i);
		else if (data->line[i] == '\'' || data->line[i] == '\"')
			i = count_quotes(data, i);
		else
		{
			while (ft_strchr("><|", data->line[i]) == NULL)
			{
				if (data->line[i] == ' ')
					break ;
				i++;
			}	
		}
		n_break++;
	}
	return (n_break);
}

static int	len_subline(t_minishell *data, int start)
{
	int	len;
	int	i;

	i = start;
	len = 0;
	printf ("valor i: %d\n", i);
	while (data->line[i] != '\0')
	{
		while (data->line[i] == ' ' && data->line[i] != '\0')
		{	
			printf ("oi\n");
			i++;
		}
		if (ft_strchr("><|" , data->line[i]) != NULL)
			len = count_tokens(data, i);
		else if (data->line[i] == '\'' || data->line[i] == '\"')
			len = count_quotes(data, i);
		else
		{
			while (ft_strchr("><|", data->line[i]) == NULL)
			{
				if (data->line[i] == ' ')
				{
					len++;
					break ;
				}
				i++;
				len++;
			}
		}
		return (len);
	}
	return (0);
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
		printf ("start %d len %d\n", start, len);
		parsed_line[i] = ft_substr(data->line, start, len);
		printf ("%s\n", parsed_line[i]);
		start = start + len;
		if (data->line[start] == '\0')
			break ;
		i++;
	}
}

void	parse_line(t_minishell *data)
{
	int		n;
	char	**parsed_line;

	n = get_n_break(data);
	if (n < 0)
		ft_putstr_fd("quote is missing\n", 1); //lembrar de tratar erro e frees e código de saída
	parsed_line = (char **)malloc(sizeof(char *) * (n + 1));
	if (!parsed_line)
		exit (1);
	split_line(parsed_line, data, n);
}
