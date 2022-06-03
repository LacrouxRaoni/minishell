/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:26:53 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/03 18:25:17 by rruiz-la         ###   ########.fr       */
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






























































static void exec_cmd(t_cmd **cmd)
{
	int	i;
	t_cmd *cmd_node;

	cmd_node = (*cmd);
	while (cmd_node != NULL)
	{
		if (cmd_node->word != NULL)
		{
			//check_bult_in();



			while (cmd_node->word[i] != NULL)
			{
				if (ft_strcmp(cmd_node->word[i], "echo") == 0)
				{
					//exec_echo	
				}
				else if (ft_strcmp(cmd_node->word[i], "cd") == 0)
				{	
					//exec_cd
				}
				else if (ft_strcmp(cmd_node->word[i], "pwd") == 0)
				{
					//exec_pwd	
				}
				else if (ft_strcmp(cmd_node->word[i], "export") == 0)
				{
					//exec_export	
				}
				else if (ft_strcmp(cmd_node->word[i], "unset") == 0)
				{
					//exec_unset	
				}
				else if (ft_strcmp(cmd_node->word[i], "env") == 0)
				{
					//exec_env	
				}
				else if (ft_strcmp(cmd_node->word[i], "exit") == 0)
				{
					//exec_exit					
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
