/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:01:55 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/16 10:41:52 by rruiz-la         ###   ########.fr       */
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
	int		n;
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
int		token_analysis(t_mns *data);
int		lexical_analysis(t_mns *data);
int		syntax_analysis(char **lexical_line);
int		get_n_break(t_mns *data, int i);
int		len_subline(t_mns *data, int start, int len, int aux);
void	cmd_table(t_mns *data, t_cmd **cmd);
void	exec_cmds(t_cmd **cmd);
void	free_cmd_table(t_cmd **cmd);
void	free_lexical_line(t_mns *data);
#endif