/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:01:55 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/08 11:47:35 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "env_list.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "./libft.h"

typedef struct s_mns
{
	char	*line;
	char	**lexical_line;
	int		error_num;
}	t_mns;

char	*print_terminal_line(char *line);
int		token_analysis(t_mns *data);
void	lexical_analysis(char **parsed_line, t_mns *data, int n);
int		get_n_break(t_mns *data, int i, int n_break);
int		len_subline(t_mns *data, int start, int len, int aux);
#endif