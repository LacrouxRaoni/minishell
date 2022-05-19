/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 21:40:00 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/18 11:48:21 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_lexical_line(char **lexical_line, int i, t_utils *utils)
{
	if (ft_strncmp(lexical_line[i], "WORD\0", 5) != 0)
	{
		if (ft_strncmp(lexical_line[i], "PIPE", 4) == 0)
			return (i);
		else if ((ft_strncmp(lexical_line[i], "DLESS", 5) == 0))
		{
			i = i + 1;
			utils->hdoc_n = utils->hdoc_n + 2;
		}
		else
		{
			i = i + 1;
			utils->red_n = utils->red_n + 2;
		}
	}
	else
		utils->cmd_n++;
	return (i);
}

static void	define_cmd_size(char **lexical_line,
			t_utils *utils, t_cmd *cmd_node)
{
	int	i;

	utils->red_n = 0;
	utils->cmd_n = 0;
	utils->hdoc_n = 0;
	i = utils->start;
	while (lexical_line[i])
	{
		i = count_lexical_line(lexical_line, i, utils);
		if (ft_strncmp(lexical_line[i], "PIPE", 4) == 0)
			break ;
		i++;
	}
	cmd_node->next = NULL;
	cmd_node->word = (char **)ft_calloc(utils->cmd_n + 1, sizeof(char *));
	if (!cmd_node->word)
		exit (1);
	cmd_node->redirect = (char **)ft_calloc(utils->red_n + 1, sizeof(char *));
	if (!cmd_node->redirect)
		exit (1);
	cmd_node->here_doc = (char **)ft_calloc(utils->hdoc_n + 1, sizeof(char *));
	if (!cmd_node->here_doc)
		exit (1);
}

static int	fulfill_cmd_table(char **lexical_line, t_utils *utils,
		t_mns *data, t_cmd *cmd_node)
{
	if (ft_strncmp(lexical_line[utils->i], "PIPE", 4) == 0)
	{
		printf ("red %s \n", cmd_node->redirect[utils->r]);
		return (-10);
	}
	else if (ft_strncmp(lexical_line[utils->i], "DLESS", 5) == 0)
	{
		cmd_node->here_doc[utils->h] = ft_strdup(data->parsed_line[utils->i]);
		cmd_node->here_doc[utils->h + 1]
			= ft_strdup(data->parsed_line[utils->i + 1]);
		printf("hdoc %s ", cmd_node->here_doc[utils->h]);
		printf("%s \n", cmd_node->here_doc[utils->h + 1]);
		utils->i++;
		utils->h++;
	}
	else
	{
		cmd_node->redirect[utils->r] = ft_strdup(data->parsed_line[utils->i]);
		cmd_node->redirect[utils->r + 1]
			= ft_strdup(data->parsed_line[utils->i + 1]);
		printf ("red %s ", cmd_node->redirect[utils->r]);
		printf ("%s \n", cmd_node->redirect[utils->r + 1]);
		utils->i++;
		utils->r++;
	}
	return (0);
}

static void	prepara_cmd_table(t_mns *data, t_utils *cmd_utils,
		t_cmd *cmd_node)
{
	int	r;

	define_cmd_size(data->lexical_line, cmd_utils, cmd_node);
	cmd_utils->w = 0;
	cmd_utils->h = 0;
	cmd_utils->r = 0;
	cmd_utils->i = cmd_utils->start;
	r = 0;
	while (data->lexical_line[cmd_utils->i])
	{
		if (ft_strncmp(data->lexical_line[cmd_utils->i], "WORD\0", 5) != 0)
		{
			r = fulfill_cmd_table(data->lexical_line,
					cmd_utils, data, cmd_node);
			if (r < 0)
				break ;
		}
		else
		{
			cmd_node->word[cmd_utils->w]
				= ft_strdup(data->parsed_line[cmd_utils->i]);
			printf ("word %s\n", cmd_node->word[cmd_utils->w]);
			cmd_utils->w++;
		}
		cmd_utils->i++;
	}
}

void	cmd_table(t_mns *data, t_cmd **cmd)
{
	t_utils	cmd_utils;
	t_cmd	*cmd_node;
	t_cmd	*last_node;

	*cmd = NULL;
	cmd_utils.start = 0;
	cmd_utils.i = 0;
	while (data->lexical_line[cmd_utils.i])
	{
		cmd_node = (t_cmd *)malloc(sizeof(t_cmd));
		if (!cmd_node)
			exit (1);
		prepara_cmd_table(data, &cmd_utils, cmd_node);
		cmd_utils.start = cmd_utils.i + 1;
		if (*cmd == NULL)
			*cmd = cmd_node;
		else
		{
			last_node = *cmd;
			while (last_node->next != NULL)
				last_node = last_node->next;
			last_node->next = cmd_node;
		}
	}
}
