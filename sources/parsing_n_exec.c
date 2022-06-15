/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_n_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:53:31 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/14 11:58:57 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_words_and_exec(void)
{
	if (word_expansion() < 0)
	{
		(g_data.mns).exit_code = 1;
		free_cmd_table();
	}
	else
	{
		//exec_cmd
		prepare_to_exec();
		free_cmd_table();
	}
}

void	parsing_and_exec(void)
{
	if (token_analysis() < 0)
	{
		if ((g_data.mns).err_num == -1)
			printf("quote is missing\n");
	}
	else
	{
		lexical_analysis();
		if (syntax_analysis() > 0)
			(g_data.mns).exit_code = 2;
		else
		{
			create_cmd_table();
			expand_words_and_exec();
		}
		free_lexical_line();
	}		
	free ((g_data.mns).line);
}
