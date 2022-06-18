/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_subline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:05:44 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/18 19:49:36 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_len_tokens(t_mns *data, int i)
{
	int	len;

	len = i;
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
	len = i - len;
	return (len);
}

static int	get_len_quotes(t_mns *data, int i)
{
	int	len;

	len = 0;
	if (data->line[i] == '\'')
	{
		len++;
		while (data->line[++i] != '\'')
			len++;
		i++;
		len++;
	}
	else if (data->line[i] == '\"')
	{
		len++;
		while (data->line[++i] != '\"')
			len++;
		i++;
		len++;
	}
	return (len);
}

int	len_subline(t_mns *data, int start, int len, int aux)
{
	while (data->line[start] == ' ' && data->line[start] != '\0')
		start++;
	if (ft_strchr("><|", data->line[start]) != NULL)
	{
		len = get_len_tokens(data, start);
		start = start + len;
	}
	else
	{
		while (ft_strchr("><| ", data->line[start]) == NULL)
		{
			if (data->line[start] == '\'' || data->line[start] == '\"')
			{
				aux = get_len_quotes(data, start);
				start = start + aux;
				len = len + aux;
			}
			else
			{
				start++;
				len++;
			}
		}
	}
	return (len);
}
