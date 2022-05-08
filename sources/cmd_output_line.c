/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_output_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 11:07:27 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/08 11:08:17 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*print_terminal_line(char *line)
{
	char	*user;
	char	dir[1024];
	char	*aux;
	char	*aux2;

	user = getenv("USER");
	getcwd(dir, sizeof(dir));
	aux = ft_strjoin(user, "@:");
	aux2 = ft_strjoin(dir, "$ ");
	line = ft_strjoin(aux, aux2);
	free (aux);
	free (aux2);
	return (line);
}
