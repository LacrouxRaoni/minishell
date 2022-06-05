/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:01:55 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/05 17:50:53 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "execve.h"
# include "env_list.h"
# include "cmd_iterator.h"
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
	char 	**word;
	char 	**redirect;
	int		fd_in;
	int		fd_out;
	char	*var_name;
	char	*content;
	struct s_cmd *next;
} t_cmd;

typedef struct	s_main
{
	t_hash *hash[2];
	t_mns	mns;
	t_cmd	*cmd;
	t_exec  exec;
}	t_main;

extern t_main g_data;

t_hash	*create_hashtable(char **variables);
void	fulfill_hash(char **envp, t_hash *hash);
char	*extract_key(char  *key_line);
char	*extract_value(char *value_line);
char	*print_terminal_line(char *line);
int		token_analysis(void);
int		lexical_analysis(void);
int		syntax_analysis(void);
int		get_n_break(t_mns *data, int i);
int		len_subline(t_mns *data, int start, int len, int aux);
void	cmd_table(void);
void	prepare_to_exec(void);
void	exec_redirect(void);
void	exec_here_doc(t_cmd *cmd_node, int i);
void	word_expansion(t_cmd *cmd_node);
int		check_for_var(t_cmd *cmd_node, int w);
int		tild_expansion(t_cmd *cmd_node, int i);
void	quote_expansion(t_cmd *cmd_node, int i);
void	handle_s_quote(t_cmd *cmd_node, int i);
void	handle_d_quotes(t_cmd *cmd_node, int i);
char	*clean_quotes(char *content);
void	parse_assignment_expansion(t_cmd *cmd_node, int i);
int		count_keys(char *word, int j);
int		count_dollars(t_cmd *cmd_node, int i, int *len, int *k);
char	*assignment_expansion(char *assi_word);
void	free_cmd_table(void);
void	free_lexical_line(void);

void	free_hash_table();


int	get_hash_pos(char *key, int size);
#endif