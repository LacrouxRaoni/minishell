/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:00:21 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/18 19:49:36 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_tokens(t_mns *data, int i)
{
	if (data->line[i] == '<')
	{
		if (data->line[i + 1] == '<')
			i++;
		i++;
	}
	else if (data->line[i] == '>')
	{
		if (data->line[i + 1] == '>')
			i++;
		i++;
	}
	else if (data->line[i] == '|')
		i++;
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

int	get_n_break(t_mns *data, int i)
{
	data->n_break = 0;
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
		data->n_break++;
	}
	return (data->n_break);
}
