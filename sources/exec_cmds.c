/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:26:53 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/15 07:56:19 by rruiz-la         ###   ########.fr       */
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




static void free_everything()
{
	free_cmd_table();
	free_lexical_line();
	rl_clear_history();
	free_envp_list();
	if (g_data.exec.path != NULL)
		free_path();
	if (g_data.exec.path_confirmed != NULL)
	{
		free (g_data.exec.path_confirmed);
		g_data.exec.path_confirmed = NULL;
	}
}

static void exec_child(t_cmd *cmd_node, t_exec *exec)
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
	if (check_if_built_in(cmd_node) == 0)
	{
		if (exec->path_confirmed != NULL)
		{
			if (execve(exec->path_confirmed, cmd_node->word, NULL) - 1)
			{
				free_everything();
				exit(1);
			}
		}
	}
	else
		exec_built_in(cmd_node);
	free_everything();
	exit(0);
}

static void call_child_process(t_cmd *cmd_node)
{
	t_exec	*exec;
	int		wstatus;

	exec = &(g_data.exec);
	exec->pid = fork();
	if (exec->pid < 0)
		exit (write (1, "Fork error\n", 14));
	if (exec->pid == 0)
	{
		exec_child(cmd_node, exec);
	}
	waitpid(exec->pid, &wstatus, 0);
	if (WIFEXITED(wstatus) != 0)
		(g_data.mns).exit_code = WEXITSTATUS(wstatus);
	printf("child %d\n", (g_data.mns).exit_code);
	if (cmd_node->next != NULL)
	{
		dup2(exec->fd[0], STDIN_FILENO);
		close (exec->fd[0]);
		close (exec->fd[1]);
	}
	if (exec->path_confirmed != NULL)
	{
		free (exec->path_confirmed);
		exec->path_confirmed = NULL;
	}
	if (exec->path != NULL)
		free_path();
}

static void	exec_slashes(t_cmd *cmd_node, int i)
{
	DIR	*dir;

	if (ft_strchr(cmd_node->word[i], '/') != NULL)
	{
		dir = opendir(cmd_node->word[i]);
		if (!dir)
		{
			write (1, "bash: ", ft_strlen("bash: "));
			perror(cmd_node->word[i]);
			(g_data.mns).exit_code = 127;
		}
		else
		{
			printf ("bash: %s: Is a directory\n", cmd_node->word[0]);
			(g_data.mns).exit_code = 126;
			closedir(dir);
		}
	}
}

static int run_cmd(t_cmd *cmd_node, int i)
{
	if (cmd_node->next != NULL)
		open_pipe();
	if (cmd_node->redirect[i] != NULL)
		init_redirects(cmd_node);
	if (cmd_node->word[i] != NULL && (g_data.mns).exit_code == 0)
	{
		if (cmd_node->expansion > 0)
			exec_slashes(cmd_node, i);



		if (ft_str_check(cmd_node->word[0], "cd"))
		{
			cd_built_in(cmd_node->word);
				return (0);
		}
		///////


		
		if (check_if_built_in(cmd_node) == 0 && g_data.mns.exit_code == 0)
		{
			if (get_path(cmd_node, i) == 1)
				return (1);
		}
		call_child_process(cmd_node);
	}
	return (0);
}

void	exec_cmd(void)
{
	t_cmd *cmd_node;
	int	i;

	cmd_node = g_data.cmd;
	g_data.exec.temp_fd = dup(STDIN_FILENO);
	g_data.exec.path_confirmed = NULL;
	g_data.exec.path = NULL;
	g_data.exec.b_hdoc = 0;
	i = 0;
	while (cmd_node != NULL)
	{
		if (run_cmd(cmd_node, i) == 1)
			break ;
		close_files(cmd_node);
		if (cmd_node->next != NULL)
		{
			(g_data.mns).exit_code = 0;
			g_data.exec.b_hdoc = 1;
		}
		cmd_node = cmd_node->next;
	}
	dup2(g_data.exec.temp_fd, STDIN_FILENO);
	close (g_data.exec.temp_fd);
}

void	prepare_to_exec()
{
	/*t_cmd	*cmd_node;
	
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
