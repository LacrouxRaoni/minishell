/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:26:53 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/06 22:47:21 by tyago-ri         ###   ########.fr       */
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



void	printf_cmd(t_cmd **cmd, int j)
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
				if (j == 0)
					printf ("cmd word: %s\n" ,cmd_node->word[i]);
				else
					printf ("new cmd word: %s\n" ,cmd_node->word[i]);
				i++;
			}
		}
		if (cmd_node->redirect[0] != NULL)
		{
			i = 0;
			while (cmd_node->redirect[i] != NULL)
			{
				if (j == 0)
				{
					printf ("fd in node %d: %d\n" , i, cmd_node->fd_in);
					printf ("fd out node %d: %d\n" , i, cmd_node->fd_out);
					printf ("cmd red: %s\n" ,cmd_node->redirect[i]);
				}
				else
				{
					printf ("new fd in node %d: %d\n" , i, cmd_node->fd_in);
					printf ("new fd out node %d: %d\n" , i, cmd_node->fd_out);
					printf ("new cmd red: %s\n" ,cmd_node->redirect[i]);
				}
				i++;
			}
		}
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
void	exec_built_in(t_cmd *cmd)
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


static void exec_child(t_cmd *cmd_node,int *fd)
{
		close(fd[0]);
		printf ("fd in %d\n", cmd_node->fd_in);
		printf ("fd in %d\n", cmd_node->fd_out);
		if (cmd_node->fd_in > 0)
			dup2(cmd_node->fd_in, STDIN_FILENO);
		if (cmd_node->next != NULL)
			dup2(fd[1], STDOUT_FILENO);
		else if (cmd_node->fd_out > 0)
			dup2(cmd_node->fd_out, STDOUT_FILENO);
		close (fd[1]);
		if (execve(g_data.exec.path_confirmed, cmd_node->word, NULL) == -1)
			exit(1);
}

static void call_child_process(t_cmd *cmd_node, int *fd)
{
	int	pid;

	if (pipe(fd) < 0)
		return ;
	pid = fork();
	if (pid < 0)
		return	;
	if (pid == 0)
	{
		exec_child(cmd_node, fd);
	}
	waitpid(pid, NULL, 0);
	if (cmd_node->next != NULL)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	free (g_data.exec.path_confirmed);
	if (cmd_node->redirect != NULL)
	{
		if (cmd_node->fd_in > 0)
			close (cmd_node->fd_in);
		if (cmd_node->fd_out > 0)
			close (cmd_node->fd_out);
	}
}

static void exec_cmd(void)	
{
	int	i;
	int	fd[2];
	int	tmp_fd;
	t_cmd *cmd_node;

	cmd_node = g_data.cmd;
	tmp_fd = dup(STDIN_FILENO);
	while (cmd_node != NULL)
	{
		if (cmd_node->redirect[0] != NULL)
			exec_redirect();
		if (cmd_node->word != NULL)
		{
			i = 0;
			while (cmd_node->word[i] != NULL)
			{
				//check_bult_in();
				if (ft_strcmp(cmd_node->word[i], "echo") == 0)
					printf ("%s\n", cmd_node->word[i]);//exec_echo
				else if (ft_strcmp(cmd_node->word[i], "cd") == 0)
					printf ("%s\n", cmd_node->word[i]);//exec_cd
				else if (ft_strcmp(cmd_node->word[i], "pwd") == 0)
					printf ("%s\n", cmd_node->word[i]);//exec_pwd
				else if (ft_strcmp(cmd_node->word[i], "env") == 0)
					printf ("%s\n", cmd_node->word[i]);//exec_env
				else if (ft_strcmp(cmd_node->word[i], "export") == 0)
					printf ("%s\n", cmd_node->word[i]);//exec_export	
				else if (ft_strcmp(cmd_node->word[i], "unset") == 0)
					printf ("%s\n", cmd_node->word[i]);//exec_unset	
				else if (ft_strcmp(cmd_node->word[i], "exit") == 0)
					printf ("%s\n", cmd_node->word[i]);//exec_exit
				else
				{
					if (check_valid_path_cmd(cmd_node, i) != 0)
					{
						printf ("cmd not found\n");
						//command not found (127)
					}
					else
					{
						call_child_process(cmd_node, fd);
						break ;
					}
				}
				i++;
			}
		}
		cmd_node = cmd_node->next;
	}
	dup2(tmp_fd, STDIN_FILENO);
}

void	prepare_to_exec()
{
	t_cmd	*cmd_node;
	//int	i;
	
	//i = 0;
	cmd_node = g_data.cmd;
	//printf_cmd(&g_data.cmd, i);
	//i++;
	while (cmd_node != NULL)
	{
		if (cmd_node->word[0] != NULL)
		{
			word_expansion(cmd_node);
			if (check_if_built_in(cmd_node))
					exec_built_in(cmd_node);
		}
		cmd_node = cmd_node->next;
	}
	//printf_cmd(&g_data.cmd, i);
	exec_cmd();
}
