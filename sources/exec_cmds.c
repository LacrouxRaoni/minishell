/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:26:53 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/11 12:41:57 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int	split_var_n_content(t_cmd *cmd_node, int w, int *i, int *j)
{
	if (ft_isalpha(cmd_node->word[w][0]) == 0)
		return (-1);
	while (cmd_node->word[w][(*i)])
	{
		if (cmd_node->word[w][(*i)] == '=')
			break ;
		else if (ft_isalnum(cmd_node->word[w][(*i)]) == 0)
			return (-1);
		else
			*j++;
		(*i)++;
	}
}

char	*clean_quotes(char *content)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] != '\'' && content[i] != '\"')
			j++;
		i++;
	}
	aux = (char *)ft_calloc(j + 1, sizeof(char *));
	i = -1;
	j = 0;
	while (content[++i])
	{
		if (content[i] != '\'' && content[i] != '\"')
		{
			aux[j] = content[i];
			j++;
		}
	}
	aux[j] = '\0';
	return (aux);
}

int	check_for_var(t_cmd *cmd_node, int w)
{
	int		i;
	int		j;
	char	*content;

	i = 0;
	j = 0;
	if (ft_strchr(cmd_node->word[w], '=') != NULL)
	{
		if (split_var_n_content(cmd_node, w, &i, &j) == -1)
			return (1);
		cmd_node->var_name = ft_substr(cmd_node->word[w], 0, i);
		if (ft_strchr(cmd_node->var_name, '\'') != NULL
			|| ft_strchr(cmd_node->var_name, '\"') != NULL)
		{
			free(cmd_node->var_name);
			return (1);
		}
		content = ft_substr(cmd_node->word[w],
				i + 1, ft_strlen(cmd_node->word[w]));
		if (ft_strchr(content, '\'') != NULL
			|| ft_strchr(content, '\"') != NULL)
			cmd_node->content = clean_quotes(content);
		else
			cmd_node->content = ft_strdup(content);
		free(content);
		printf ("var name: %s\n", cmd_node->var_name);
		printf ("content: %s\n", cmd_node->content);
	}
	return (0);
}

































void	printf_cmd(t_cmd **cmd)
{
	int i;
	t_cmd *cmd_node;

	cmd_node = (*cmd);

	while (cmd_node != NULL)
	{
		if (cmd_node->word[0] != NULL)
		{
			i = 0;
			while (cmd_node->word[i] != NULL)
			{
				printf ("cmd word: %s\n" ,cmd_node->word[i]);
				i++;
			}
		}
		if (cmd_node->redirect[0] != NULL)
		{
			i = 0;
			while (cmd_node->redirect[i] != NULL)
			{
					printf ("fd in node %d: %d\n" , i, cmd_node->fd_in);
					printf ("fd out node %d: %d\n" , i, cmd_node->fd_out);
					printf ("cmd red: %s\n" ,cmd_node->redirect[i]);
				i++;
			}
		}
		printf ("PIPE\n");
		cmd_node = cmd_node->next;
	}
}



























int	check_if_built_in(t_cmd *cmd)
{
	if (ft_str_check(cmd->word[0], "echo"))
		return (1);
	else if (ft_str_check(cmd->word[0], "pwd"))
		return (1);
	else if (ft_str_check(cmd->word[0], "env"))
		return (1);
	// else if (ft_str_check(cmd->word[0], "cd"))
	// 	return (1);
	else
		return (0);
}
void	exec_built_in(t_cmd *cmd, int *fd)
{
	if (ft_str_check(cmd->word[0], "echo"))
		echo_built_in(cmd->word);
	else if (ft_str_check(cmd->word[0], "pwd"))
		pwd_built_in();
	else if (ft_str_check(cmd->word[0], "env"))
		env_built_in(cmd->word);
// 	else if (ft_str_check(cmd->word[0], "cd"))
// 		cd_built_in(cmd->word);		
}









static char  **get_path()
{
	t_env_list *table;
	int		index;
	char	**path;

	index = get_hash_pos("PATH", g_data.hash[0]->size);
	table = g_data.hash[0]->list[index];
	while (table != NULL)
	{
		if (ft_strcmp(table->key, "PATH") == 0)
		{	
			path = ft_split(table->value, ':');
			return (path);
		}
		table = table->next;	
	}
	return (NULL);
}

static void free_path(void)
{
	int	i;

	i = -1;
	while (g_data.exec.path[++i] != NULL)
		free(g_data.exec.path[i]);
	free (g_data.exec.path);
	g_data.exec.path = NULL;
}


static int	check_valid_path_cmd(t_cmd *cmd_node, int i)
{
	t_exec *exec;
	int		j;
	char	*aux;
	
	exec = &(g_data.exec);
	exec->path = get_path();
		//escrever sobre null
	if (cmd_node->word[i][0] == '/')
	{
		exec->path_confirmed = ft_strdup(cmd_node->word[i]);
		if (access(exec->path_confirmed, F_OK) == 0)
			return (0);
	}
	j = 0;
	while (exec->path[j])
	{
		aux = ft_strjoin(exec->path[j], "/");
		exec->path_confirmed = ft_strjoin(aux, cmd_node->word[i]);
		if (access(exec->path_confirmed, F_OK) == 0)
		{
			free_path();
			free (aux);
			return (0);
		}
		free (aux);
		free (exec->path_confirmed);
		exec->path_confirmed = NULL;
		j++;
	}
	free_path();
	return (1);
}







static void free_everything()
{
	free_cmd_table();
	free_lexical_line();		
	rl_clear_history();
	free_hash_table();
	free_envp_list();
	free (g_data.exec.path_confirmed);
}

static void exec_child(t_cmd *cmd_node)
{
	int	pid;
	t_exec *exec;

	exec = &(g_data.exec);
	pid = fork();
	if (pid < 0)
		exit (1);
	if (pid == 0)
	{
		if (cmd_node->next != NULL)
		{
			dup2(exec->fd[1], STDOUT_FILENO);
			close (exec->fd[0]);
			close (exec->fd[1]);
		}
		if (cmd_node->fd_out > 0)
		{
			dup2(cmd_node->fd_out, STDOUT_FILENO);
		}
		if (exec->error == 0)
		{
			if (execve(exec->path_confirmed, cmd_node->word, NULL) - 1)
				exit(write (1, "execve returned an error\n", 30));
		}
		else
		{
			free_everything();
			exit(0);
		}
	}
	waitpid(pid, NULL, 0);
	if (cmd_node->next != NULL)
	{
		printf ("oi aqui\n");
		dup2(exec->fd[0], STDIN_FILENO);
		close (exec->fd[0]);
		close (exec->fd[1]);
	}
	cmd_node->fd_out = 0;
	free (exec->path_confirmed);
}

void	open_pipe()
{
	t_exec *exec;

	exec = &(g_data.exec);
	if (pipe(exec->fd) < 0)
		exit (write (1, "Pipe error\n", 14));
}

int	exec_cmd(void)
{
	t_cmd *cmd_node;
	DIR	*dir;
	int	tfd;
	int	i;

	tfd = dup(STDIN_FILENO);
	cmd_node = g_data.cmd;
	i = 0;
	while (cmd_node != NULL)
	{
		g_data.exec.error = 0;
		if (cmd_node->next != NULL)
			open_pipe();
		if (cmd_node->redirect[i] != NULL)
		{
			exec_redirect(cmd_node);
			dup2(cmd_node->fd_in, STDIN_FILENO);
		}
		if (cmd_node->word[i] != NULL)
		{
			if (cmd_node->expansion > 0)
			{	
				if (ft_strchr(cmd_node->word[i], '/') != NULL)
				{
					dir = opendir(cmd_node->word[i]);
					if (!dir)
					{
						write (1, "bash: ", ft_strlen("bash: "));
						perror(cmd_node->word[i]);
						g_data.mns.exit_code = 127;
					}
					else
					{
						printf ("bash: %s: Is a directory\n", cmd_node->word[0]);
						closedir(dir);
					}
					break ;
				}
			}
			if (check_valid_path_cmd(cmd_node, i) != 0)
			{
				if (cmd_node->next == NULL)
				{
					write (1, cmd_node->word[i], ft_strlen(cmd_node->word[i]));
					write (1, ": command not found\n", 21);
					g_data.mns.exit_code = 127;
					break ;
				}
				write (1, cmd_node->word[i], ft_strlen(cmd_node->word[i]));
				write (1, ": command not found\n", 21);
				g_data.exec.error = 1;
			}
			exec_child(cmd_node);
		}
		cmd_node = cmd_node->next;
	}
	dup2(tfd, STDIN_FILENO);
	return (0);
}









void	prepare_to_exec()
{
/*	t_cmd	*cmd_node;
	
	int	i;
	i = 0;
	cmd_node = g_data.cmd;
	while (cmd_node != NULL)
	{
		exec_redirect(cmd_node);
		cmd_node = cmd_node->next;
	} 
	printf_cmd(&g_data.cmd);

*/	
	exec_cmd();
}
