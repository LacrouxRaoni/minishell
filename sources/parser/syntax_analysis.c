/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analysis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:31:32 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/18 19:49:36 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_error(char *word)
{
	if (ft_strncmp(word, "PIPE", 4) == 0)
		printf ("minishell: syntax error near unexpected token `|'\n");
	else if (ft_strncmp(word, "GREAT", 5) == 0)
		printf ("minishell: syntax error near unexpected token `>'\n");
	else if (ft_strncmp(word, "DGREAT", 6) == 0)
		printf ("minishell: syntax error near unexpected token `>>'\n");
	else if (ft_strncmp(word, "LESS", 2) == 0)
		printf ("minishell: syntax error near unexpected token `<'\n");
	else if (ft_strncmp(word, "DLESS", 3) == 0)
		printf ("minishell: syntax error near unexpected token `<<'\n");
	else
		printf ("minishell: syntax error near unexpected token `newline'\n");
}

static int	check_lexical_line_size_n_errors(char **lexical_line)
{
	int	i;

	i = 0;
	while (lexical_line[i])
		i++;
	if (ft_strncmp(lexical_line[0], "PIPE", 4) == 0)
	{
		print_error("PIPE");
		return (-1);
	}
	if (ft_strncmp(lexical_line[i - 1], "WORD", 4) != 0)
	{
		if (ft_strncmp(lexical_line[i - 1], "PIPE", 4) == 0)
			print_error(lexical_line[i - 1]);
		else
			print_error(lexical_line[i - 1]);
		return (-1);
	}
	return (0);
}

static int	loop_lexical_line(char **lexical_line, int i)
{
	if (ft_strncmp(lexical_line[i], "PIPE", 4) == 0)
	{
		if (ft_strncmp(lexical_line[i + 1], "PIPE", 4) == 0)
			return (-1);
	}
	else if (ft_strncmp(lexical_line[i], "WORD", 4) != 0)
	{
		if (ft_strncmp(lexical_line[i + 1], "WORD", 4) != 0)
			return (-1);
	}
	return (i);
}

int	syntax_analysis(void)
{
	int		i;
	char	**lexical_line;

	lexical_line = g_data.mns.lexical_line;
	i = check_lexical_line_size_n_errors(lexical_line);
	if (i < 0)
		return (2);
	while (lexical_line[i])
	{
		i = loop_lexical_line(lexical_line, i);
		if (i < 0)
		{
			print_error(lexical_line[i + 1]);
			return (2);
		}		
		i++;
	}
	return (0);
}
