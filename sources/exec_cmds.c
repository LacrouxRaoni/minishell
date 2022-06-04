/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:26:53 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/04 17:30:53 by rruiz-la         ###   ########.fr       */
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


























































static char  **get_path()
{
	t_env_list *table;
	int		index;
	char	**path;

	index = get_hash_pos("PATH", g_data.hash[0]->size);
	table = g_data.hash[0]->list[index];
	while (table != NULL)
	{
		if (strcmp(table->key, "PATH") == 0)
		{	
			path = ft_split(table->value, ':');
			return (path);
		}
		table = table->next;	
	}
	return (NULL);
}

static void free_path(char ***path)
{
	int	i;

	i = -1;
	while ((*path)[++i] != NULL)
		free((*path)[i]);
	free ((*path));
	(*path) = NULL;
}


static int	check_valid_path_cmd(t_cmd *cmd_node, int i)
{
	t_exec pipex;
	int		j;
	char	*aux;
	
	pipex.path = get_path();
	if (cmd_node->word[i][0] == '/')
	{
		pipex.path_confirmed = ft_strdup(cmd_node->word[i]);
		if (access(pipex.path_confirmed, F_OK) == 0)
			return (0);
	}
	j = 0;
	while (pipex.path[j])
	{
		aux = ft_strjoin(pipex.path[j], "/");
		pipex.path_confirmed = ft_strjoin(aux, cmd_node->word[i]);
		if (access(pipex.path_confirmed, F_OK) == 0)
		{
			free_path(&pipex.path);
			free (aux);
			return (0);
		}
		free (aux);
		free (pipex.path_confirmed);
		pipex.path_confirmed = NULL;
		j++;
	}
	return (1);
}

static void exec_child(t_cmd *cmd_node, int *fd, t_exec *pipex)
{
		close(fd[0]);
		if (cmd_node->next != NULL)
			dup2(fd[1], STDOUT_FILENO);
		close (fd[1]);
		if (execve(pipex->path_confirmed, cmd_node->word, NULL) == -1)
			exit(1);
		else
			exit (1);
}

static void call_child_process(t_cmd *cmd_node, int i)
{
	t_exec pipex;
	int	fd[2];
	int	pid;

	if (pipe(fd) < 0)
		return ;
	pid = fork();
	if (pid < 0)
		return	;
	if (pid == 0)
	{
		exec_child(cmd_node, fd, &pipex);
	}
	waitpid(pid, NULL, 0);
	if (cmd_node->next != NULL)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}





























static void exec_cmd(t_cmd **cmd)	
{
	int	i;
	t_cmd *cmd_node;

	cmd_node = (*cmd);
	while (cmd_node != NULL)
	{
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
				else if (ft_strcmp(cmd_node->word[i], "export") == 0)
					printf ("%s\n", cmd_node->word[i]);//exec_export	
				else if (ft_strcmp(cmd_node->word[i], "unset") == 0)
					printf ("%s\n", cmd_node->word[i]);//exec_unset	
				else if (ft_strcmp(cmd_node->word[i], "env") == 0)
					printf ("%s\n", cmd_node->word[i]);//exec_env
				else if (ft_strcmp(cmd_node->word[i], "exit") == 0)
					printf ("%s\n", cmd_node->word[i]);//exec_exit
				else
				{
					if (check_valid_path_cmd(cmd_node, i) != 0)
					{
						//command not found (127)
					}
					else
					{
						call_child_process(cmd_node, i);
					}
				}
				i++;
			}
		}
	
		cmd_node = cmd_node->next;
	}
}

void	prepare_to_exec(t_cmd **cmd)
{
	t_cmd *cmd_node;
	//int	i;
	
	//i = 0;
	cmd_node = (*cmd);
	//printf_cmd(cmd, i);
	//i++;
	while (cmd_node != NULL)
	{
		if (cmd_node->word[0] != NULL)
			word_expansion(cmd_node);
		cmd_node = cmd_node->next;
	}
	//if (cmd_node->redirect[0] != NULL)
	//	exec_redirect(cmd, cmd_node);
	//printf_cmd(cmd, i);
	exec_cmd(cmd);
}
