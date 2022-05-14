/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:14:21 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/12 11:11:50 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sort_lexical_line(char **parsed_line, int i, t_mns *data)
{
	if (ft_strncmp(parsed_line[i], "|", 1) == 0)
	data->lexical_line[i] = ft_strdup("PIPE");
	else if (ft_strncmp(parsed_line[i], "<\0", 2) == 0)
		data->lexical_line[i] = ft_strdup("LESS");
	else if ((ft_strncmp(parsed_line[i], "<<\0", 3) == 0))
		data->lexical_line[i] = ft_strdup("DLESS");
	else if ((ft_strncmp(parsed_line[i], "<<<\0", 4) == 0))
		data->lexical_line[i] = ft_strdup("GLESS");
	else if ((ft_strncmp(parsed_line[i], ">\0", 2) == 0))
		data->lexical_line[i] = ft_strdup("GREAT");
	else if ((ft_strncmp(parsed_line[i], ">>\0", 3) == 0))
		data->lexical_line[i] = ft_strdup("DGREAT");
	else if ((ft_strncmp(parsed_line[i], ">|\0", 3) == 0))
		data->lexical_line[i] = ft_strdup("CLOOPER");
	else
		data->lexical_line[i] = ft_strdup("WORD");
	return (i);
}

int	lexical_analysis(char **parsed_line, t_mns *data, int n)
{
	int	i;

	data->lexical_line = (char **)ft_calloc(n + 1, sizeof(char *));
	if (!data->lexical_line)
		exit (1);
	data->error_num = 0;
	i = 0;
	while (parsed_line[i] != NULL)
	{
		i = sort_lexical_line(parsed_line, i, data);
		printf ("%s ", data->lexical_line[i]);
		i++;
	}
	printf ("\n");
	data->error_num = syntax_analysis(data->lexical_line);
	if (data->error_num == 2)
		return (2);
	return (0);
}
