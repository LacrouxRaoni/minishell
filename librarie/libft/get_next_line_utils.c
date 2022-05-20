/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 18:44:50 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/20 11:51:55 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_reader(char **backup_buffer, int bytes_read)
{
	int	i;
	
	i = -1;
	while (*backup_buffer[++i])
		free(backup_buffer[i]);
	free(*backup_buffer);
	*backup_buffer = NULL;	
	return (bytes_read);
}

char	*gnl_join(char **s1, char **s2)
{
	char	*swap;

	swap = *s1;
	*s1 = ft_strjoin((const char *)swap, (const char *)*s2);
	free(swap);
	swap = NULL;
	return (*s1);
}
