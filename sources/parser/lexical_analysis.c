/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:14:21 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/18 19:49:36 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_lexical_line(void)
{
	int		i;
	t_mns	*data;

	data = &(g_data.mns);
	if (data->lexical_line != NULL)
	{
		i = -1;
		while (data->lexical_line[++i])
			free (data->lexical_line[i]);
		free(data->lexical_line);
		data->lexical_line = NULL;
	}
	if (data->parsed_line != NULL)
	{
		i = -1;
		while (data->parsed_line[++i])
			free (data->parsed_line[i]);
		free(data->parsed_line);
		data->parsed_line = NULL;
	}
}

static int	sort_lexical_line(int i, t_mns *data)
{
	if (ft_strncmp(data->parsed_line[i], "|", 1) == 0)
	data->lexical_line[i] = ft_strdup("PIPE");
	else if (ft_strncmp(data->parsed_line[i], "<\0", 2) == 0)
		data->lexical_line[i] = ft_strdup("LESS");
	else if ((ft_strncmp(data->parsed_line[i], "<<\0", 3) == 0))
		data->lexical_line[i] = ft_strdup("DLESS");
	else if ((ft_strncmp(data->parsed_line[i], ">\0", 2) == 0))
		data->lexical_line[i] = ft_strdup("GREAT");
	else if ((ft_strncmp(data->parsed_line[i], ">>\0", 3) == 0))
		data->lexical_line[i] = ft_strdup("DGREAT");
	else
		data->lexical_line[i] = ft_strdup("WORD");
	return (i);
}

int	lexical_analysis(void)
{
	int		i;
	t_mns	*data;

	data = &(g_data.mns);
	data->lexical_line = (char **)ft_calloc(data->n + 1, sizeof(char *));
	if (!data->lexical_line)
		exit (1);
	i = 0;
	while (data->parsed_line[i] != NULL)
	{
		i = sort_lexical_line(i, data);
		i++;
	}
	return (0);
}
