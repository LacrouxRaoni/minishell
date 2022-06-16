/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyago-ri <tyago-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:38:52 by tyago-ri          #+#    #+#             */
/*   Updated: 2022/06/06 22:38:52 by tyago-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	no_dir_error(char **cmd)
{
	g_data.mns.exit_code = 1;
	ft_putstr_fd("cd: ", STDERR);
	ft_putstr_fd(cmd[1], STDERR);
	if (access(cmd[1], F_OK) == 0)
		ft_putstr_fd(": Not a directory\n", STDERR);
	else
		ft_putstr_fd(": No such file or directory\n", STDERR);
}

static void	cd_to_oldpwd(void)
{
	if (find_env("OLDPWD") == NULL)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR);
		return ;
	}
	chdir(find_env("OLDPWD"));
	ft_putstr_fd(find_env("OLDPWD"), STDOUT);
	write (1, "\n", 1);
}

static void	change_pwd(void)
{
	char	*buf;
	char	*old_pwd;
	char	*cwd;
	char	*aux;

	if (find_env("PWD") == NULL)
		return ;
	buf = malloc (1024);
	aux = ft_strdup("OLDPWD=");
	old_pwd = ft_strjoin(find_env("PWD"), aux);
	free(aux);
	aux = ft_strdup("PWD=");
	cwd = ft_strjoin(aux, getcwd(buf, 1024));
	do_export(cwd);
	do_export(old_pwd);
	free (aux);
	free (cwd);
	free (old_pwd);
	free (buf);
}

int	check_dir(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	cd_built_in(char **cmd)
{
	if (g_data.cmd->next != NULL)
		return ;
	g_data.mns.exit_code = 0;
	if (cmd[1] == NULL || ft_str_check(cmd[1], "~"))
	{
		if (find_env("HOME") == NULL)
			return ;
		chdir (find_env("HOME"));
		change_pwd();
	}
	else if (cmd[2] != NULL)
	{
		g_data.mns.exit_code = 1;
		ft_putstr_fd("cd: too many arguments\n", STDERR);
	}
	else
	{
		if (ft_str_check(cmd[1], "-"))
			cd_to_oldpwd();
		else if (access(cmd[1], F_OK) == 0 && check_dir(cmd[1]) == 1)
			chdir(cmd[1]);
		else
			no_dir_error(cmd);
		change_pwd();
	}
}
