/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 21:05:56 by tyago-ri          #+#    #+#             */
/*   Updated: 2022/06/10 21:05:56 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_list(void)
{
	char	**sorted_env;
	int		i;
	int		j;

	i = -1;
	sorted_env = get_sorted_env();
	while (sorted_env[++i] != NULL)
	{
		j = -1;
		if (ft_isalpha(sorted_env[i][0]))
		{
			ft_putstr_fd("declare -x ", STDOUT);
			while (sorted_env[i][++j] != '=' && sorted_env[i][j] != '\0')
				ft_putchar_fd(sorted_env[i][j], STDOUT);
			if (sorted_env[i][j] == '=')
			{
				ft_putchar_fd('=', STDOUT);
				ft_putchar_fd('\"', STDOUT);
				ft_putstr_fd(sorted_env[i] + j + 1, STDOUT);
				ft_putchar_fd('\"', STDOUT);
			}
			ft_putchar_fd('\n', STDOUT);
		}
	}
	free_split (sorted_env);
}

static void	add_node(char *temp)
{
	t_env_list	*node;
	t_env_list	*last;
	int	i;

	i = 0;
	node = (g_data.list);
	while (ft_strncmp((g_data.exec).env[i], temp, ft_strlen(temp)) != 0)
		i++;
	while (node->next != NULL)
	{
		if (ft_strncmp(node->key, temp, ft_strlen(temp)) == 0)
		{
			free(node->value);
			node->value = extract_value(g_data.exec.env[i]);
			return ;
		}
		node = node->next;
	}
	if (node->next == NULL)
	{
		last = (t_env_list *)ft_calloc(1, sizeof(t_env_list));
		last->next = NULL;
		last->key = extract_key(g_data.exec.env[i]);
		last->value = extract_value(g_data.exec.env[i]);
		node->next = last;
	}
}


void	export_add(char *var, char *temp)
{
	int		size;
	int		i;
	char	**str;

	size = 0;
	i = -1;
	while (g_data.exec.env[size] != NULL)
		size++;
	str = (char **) malloc (sizeof(char *) * (size + 2));
	while (g_data.exec.env[++i] != NULL)
	{
		if (i == size - 2)
		{
			str[i] = ft_strdup(g_data.exec.env[i]);
			i++;
			str[i] = ft_strdup(var);
			i++;
			str[i] = ft_strdup(g_data.exec.env[i - 1]);
			break ;
		}
		str[i] = ft_strdup(g_data.exec.env[i]);
	}
	str[size + 1] = NULL;
	free_split (g_data.exec.env);
	g_data.exec.env = str;
	add_node(temp);
}

void	do_export(char *var)
{
	int		i;
	char	*temp;

	i = 0;
	while (var[i] != '=' && var[i] != '\0')
		i++;
	temp = ft_substr(var, 0, i);
	if (ft_strchr(var, '=') != NULL && find_env(temp) != NULL)
		remove_from_env(temp);
	if (find_env(temp) == NULL)
		export_add(var, temp);
	free (temp);
}

int	check_export_var(char *var)
{
	int	i;

	if (ft_isalpha(var[0]) == 0)
		return (0);
	i = -1;
	while (var[++i] != '\0' && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (0);
	}
	return (1);
}

void	export_built_in(char **cmd)
{
	int	i;

	i = 0;
	g_data.mns.exit_code = 0;
	if (cmd[1] == NULL)
	{
		export_list();
		return ;
	}
	while (cmd[++i] != NULL)
	{
		if (check_export_var(cmd[i]))
			do_export(cmd[i]);
		else
		{
			ft_putstr_fd("export: `", STDERR);
			ft_putstr_fd(cmd[i], STDERR);
			ft_putstr_fd("\': not a valid identifier\n", STDERR);
			g_data.mns.exit_code = 1;
		}
	}
}
