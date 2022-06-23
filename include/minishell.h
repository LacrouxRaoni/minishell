/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:01:55 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/23 18:31:07 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "exec.h"
# include "env_list.h"
# include "cmd_iterator.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include "../librarie/libft/libft.h"

typedef struct s_mns
{
	char	*line;
	char	*line_cmd;
	char	**lexical_line;
	char	**parsed_line;
	int		err_num;
	int		n_break;
	int		n;
	int		exit_code;
}	t_mns;

typedef struct s_cmd
{
	char			**word;
	char			**redirect;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_main
{
	t_mns		mns;
	t_cmd		*cmd;
	t_env_list	*list;
	t_exec		exec;
}	t_main;
//
extern t_main	g_data;
void	create_envp_list(void);
char	*extract_key(char *key_line);
char	*extract_value(char *value_line);
char	**workspace_env(char **env);
char	**copy_env(char **env);
void	free_envp_list(void);
//
void	exec_prompt(void);
//
void	parsing_and_exec(void);
//
int		token_analysis(void);
int		lexical_analysis(void);
int		syntax_analysis(void);
int		get_n_break(t_mns *data, int i);
int		len_subline(t_mns *data, int start, int len, int aux);
//
void	create_cmd_table(void);
void	cmd_table(t_cmd *cmd_node, t_mns *data, t_cmd *last_node);
//
int		word_expansion(void);
int		tild_expansion(t_cmd *cmd_node, int i);
int		quote_expansion(t_cmd *cmd_node, int i);
int		handle_s_quote(t_cmd *cmd_node, int i);
int		handle_d_quotes(t_cmd *cmd_node, int i);
char	*clean_quotes(char *content);
int		parse_assignment_expansion(t_cmd *cmd_node, int i);
void	free_aux_assig(char ***tmp);
int		count_keys(char *word, int j);
int		count_dollars(t_cmd *cmd_node, int i, int *len, int *k);
char	*assignment_expansion(char *assi_word);
//
void	exec_cmd(void);
//
void	open_pipe(void);
int		init_redirects(t_cmd *cmd_node);
void	exec_here_doc(t_cmd *cmd_node, int i);
void	exec_redirect(t_cmd *cmd_node);
void	close_files(t_cmd *cmd_node);
//
int		check_if_built_in(t_cmd *cmd);
void	exec_built_in(t_cmd *cmd);
int		check_n_exec_special_built_in(t_cmd *cmd_node);
void	call_child_process(t_cmd *cmd_node);
//
int		get_path(t_cmd *cmd_node, int i);
//
void	free_line(void);
void	free_envp_list(void);
void	free_list(void);
void	free_cmd_table(void);
void	free_lexical_line(void);
void	free_path(void);
void	free_everything(void);
//
char	*find_env(char *var);
char	**get_sorted_env(void);
void	env_built_in(char **cmd);
//
void	exec_built_in(t_cmd *cmd);
int		check_if_built_in(t_cmd *cmd);
//
int		ft_str_check(const char *s1, const char *s2);
int		ft_str_isnum(char *str);
void	free_split(char **s);
//
void	echo_built_in(char **cmd);
void	pwd_built_in(void);
//
void	cd_built_in(char **cmd);
//
void	remove_from_env(char *var);
void	do_export(char *var);
void	export_add(char *var);
void	free_split(char **s);
//
void	exit_built_in(char **cmd);
//
void	export_list(void);
int		check_export_var(char *var);
void	export_built_in(char **cmd);
void	unset_built_in(char	**cmd);
void	kill_loop(int signum);
void	quit_core(int signum);

#endif
