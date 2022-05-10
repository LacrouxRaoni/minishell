/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:14:21 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/09 12:22:25 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_analysist(char **lexical_line)
{
	int	i;

	i = 0;
	while (lexical_line[i])
		i++;
	if (ft_strncmp(lexical_line[0], "PIPE", 4) == 0)
	{
		printf ("minishell: syntax error near unexpected token `|'\n");
		return (2);
	}
	if (ft_strncmp(lexical_line[i - 1], "WORD", 4) != 0)
	{
		if (ft_strncmp(lexical_line[i - 1], "PIPE", 4) == 0)
			printf ("minishell: syntax error near unexpected token `|'\n");
		else
			printf ("minishell: syntax error near unexpected token `newline'\n");
		return (2);
	}
	i = 0;
	while (lexical_line[i])
	{
		if (ft_strncmp(lexical_line[i], "PIPE", 4) == 0)
		{
			if (ft_strncmp(lexical_line[i + 1], "PIPE", 4) == 0)
			{
				printf ("minishell: syntax error near unexpected token `|'\n");
				return (2);
			}
		}
		else if (ft_strncmp(lexical_line[i], "LESS", 4) == 0)
		{
			if (ft_strncmp(lexical_line[i + 1], "WORD", 4) != 0)
			{
				printf ("minishell: syntax error near unexpected token `newline'\n");
				return (2);
			}
		}
		else if (ft_strncmp(lexical_line[i], "DLESS", 4) == 0)
		{
			if (ft_strncmp(lexical_line[i + 1], "WORD", 4) != 0)
			{
				printf ("minishell: syntax error near unexpected token `newline'\n");
				return (2);
			}
		}
		else if (ft_strncmp(lexical_line[i], "GLESS", 4) == 0)
		{
			if (ft_strncmp(lexical_line[i + 1], "WORD", 4) != 0)
			{
				printf ("minishell: syntax error near unexpected token `newline'\n");
				return (2);
			}
		}
		else if (ft_strncmp(lexical_line[i], "GREAT", 4) == 0)
		{
			if (ft_strncmp(lexical_line[i + 1], "WORD", 4) != 0)
			{
				printf ("minishell: syntax error near unexpected token `newline'\n");
				return (2);
			}
		}
		else if (ft_strncmp(lexical_line[i], "DGREAT", 4) == 0)
		{
			if (ft_strncmp(lexical_line[i + 1], "WORD", 4) != 0)
			{
				printf ("minishell: syntax error near unexpected token `newline'\n");
				return (2);
			}
		}
		else if (ft_strncmp(lexical_line[i], "CLOOPER", 4) == 0)
		{
			if (ft_strncmp(lexical_line[i + 1], "WORD", 4) != 0)
			{
				printf ("minishell: syntax error near unexpected token `newline'\n");
				return (2);
			}
		}
		i++;
	}
	return (0);
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
		printf ("%s ", data->lexical_line[i]);
		i++;
	}
	printf ("\n");
	data->error_num = syntax_analysist(data->lexical_line);
	if (data->error_num == 2)
		return (2);
	return (0);
}
