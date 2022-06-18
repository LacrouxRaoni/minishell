/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 10:54:16 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/06/18 10:54:55 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_exec
{
	char	**env;
	char	*path_confirmed;
	char	**path;
	int		fd[2];
	int		temp_fd;
	int		b_hdoc;
	int		pid;
	int		error;
	int		in_exec;
}	t_exec;
#endif
