/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:00:21 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/08 11:00:23 by rruiz-la         ###   ########.fr       */
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

static int	count_quotes(t_mns *data, int i)
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

int	get_n_break(t_mns *data, int i, int n_break)
{
	while (data->line[i] != '\0')
	{
		while (data->line[i] == ' ' && data->line[i] != '\0')
			i++;
		if (ft_strchr("><|", data->line[i]) != NULL)
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
