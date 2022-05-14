/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:01:55 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/14 18:16:14 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "env_list.h"
# include "cmd_utils.h"
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
	char	**parsed_line;
	int		error_num;
	int		n_break;
}	t_mns;

typedef struct s_cmd
{
	//cmd, redirec, here_doc
	char **word;
	char **redirect;
	char **here_doc;
	struct s_cmd *next;
} t_cmd;

char	*print_terminal_line(char *line);
int		token_analysis(t_mns *data, t_cmd **cmd);
int		lexical_analysis(char **parsed_line, t_mns *data, int n);
int		syntax_analysis(char **lexical_line);
int		get_n_break(t_mns *data, int i);
int		len_subline(t_mns *data, int start, int len, int aux);
void	cmd_table(char **parsed_line, t_mns *data, t_cmd **cmd);
#endif