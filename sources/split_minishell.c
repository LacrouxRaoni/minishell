/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:26:32 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/04/27 22:26:59 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_tokens(t_mns *data, int i)
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

static int count_quotes(t_mns *data, int i)
{
	if (data->line[i] == '\'')
	{
		i++;
		while (data->line[i] != '\'')
		{
			if (data->line[i] == '\0')
				return (-1);
			i++;
		}
		i++;
	}
	else if (data->line[i] == '\"')
	{
		i++;
		while (data->line[i] != '\"')
		{
			if (data->line[i] == '\0')
				return (-1);
			i++;
		}
		i++;
	}
	return (i);
}

static int	get_n_break(t_mns *data)
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
		else
		{
			while (ft_strchr("><| ", data->line[i]) == NULL)
			{
				if (data->line[i] == '\'' || data->line[i] == '\"')
				{
					i = count_quotes(data, i);
					if (i < 0)
						return (-1);
				}
				else
					i++;
			}	
		}
		n_break++;
	}
	return (n_break);
}

static int	get_len_tokens(t_mns *data, int i)
{
	int len;

	len = 0;
	if (data->line[i] == '<')
	{

		if (data->line[i + 1] == '<')
		{
			i++;
			len++;
		}
		if (data->line[i + 1] == '<')
		{
			i++;
			len++;
		}
		i++;
		len++;
	}
	else if (data->line[i] == '>')
	{
		if (data->line[i + 1] == '>')
		{
			i++;
			len++;
		}
		else if (data->line[i + 1] == '|')
		{
			i++;
			len++;
		}
		i++;
		len++;
	}
	else if (data->line[i] == '|')
	{
		i++;
		len++;
	}
	return (len);
}

static int get_len_quotes(t_mns *data, int i)
{
	int len;

	len = 0;
	if (data->line[i] == '\'')
	{
		i++;
		len++;
		while (data->line[i] != '\'')
		{
			i++;
			len++;
		}
		i++;
		len++;
	}
	else if (data->line[i] == '\"')
	{
		i++;
		len++;
		while (data->line[i] != '\"')
		{
			i++;
			len++;
		}
		i++;
		len++;
	}
	return (len);
}

static int	len_subline(t_mns *data, int start)
{
	int	len;
	int	i;
	int aux;

	aux = 0;
	i = start;
	len = 0;
	while (data->line[i] != '\0')
	{
		while (data->line[i] == ' ' && data->line[i] != '\0')
			i++;
		if (ft_strchr("><|" , data->line[i]) != NULL)
		{
			len = get_len_tokens(data, i);
			i = i + len;
		}
		else
		{
			while (ft_strchr("><| ", data->line[i]) == NULL)
			{
				if (data->line[i] == '\'' || data->line[i] == '\"')
				{
					aux = get_len_quotes(data, i);
					i = i + aux;
					len = len + aux;
				}
				else
				{
					i++;
					len++;
				}
			}
		}
		return (len);
	}
	return (0);
}

static char	**split_line(char **parsed_line, t_mns *data, int n)
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
		start = start + len;
		while (data->line[start] == ' ')
		{
			start++;
		}
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
	int i;

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
	char	**parsed_line;

	n = get_n_break(data);
	if (n < 0)
	{
		return (-1);
	}
	parsed_line = (char **)ft_calloc(n + 1, sizeof(char *));
	if (!parsed_line)
		exit (1);
	parsed_line = split_line(parsed_line, data, n);
	lexical_analysis(parsed_line, data);
	free_parsed_line(parsed_line);
	return (0);
}
