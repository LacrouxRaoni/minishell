/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rruiz-la <rruiz-la@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 18:44:47 by rruiz-la          #+#    #+#             */
/*   Updated: 2022/05/20 11:01:27 by rruiz-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	arrange_backup(char **backup_buffer, int *i)
{
	int		j;

	j = 0;
	while ((*backup_buffer)[*i + j] != '\0')
	{
		(*backup_buffer)[j] = (*backup_buffer)[*i + j];
		j++;
	}
	(*backup_buffer)[j] = '\0';
}

char	*extract_line(char **backup_buffer)
{
	char	*line;
	int		i;

	line = (char *)malloc(sizeof(char) * (ft_strlen(*backup_buffer) + 1));
	if (!line)
	{
		free (line);
		return (NULL);
	}
	i = 0;
	while ((*backup_buffer)[i] != '\n' && (*backup_buffer)[i] != '\0')
	{
		line[i] = (*backup_buffer)[i];
		i++;
	}
	if ((*backup_buffer)[i] == '\n')
	{
		line[i] = (*backup_buffer)[i];
		i++;
		line[i] = '\0';
	}
	else
		line[i] = '\0';
	arrange_backup(backup_buffer, &i);
	return (line);
}

int	read_file(int fd, char **buffer, char **buffer_backup)
{
	int	i;
	int	bytes_read;
	int	flag;

	flag = 0;
	bytes_read = 1;
	while (flag == 0 && bytes_read > 0)
	{
		bytes_read = read(fd, *buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free_reader(buffer_backup, bytes_read));
		(*buffer)[bytes_read] = '\0';
		*buffer_backup = gnl_join(buffer_backup, buffer);
		i = 0;
		while ((*buffer)[i] != '\0')
		{
			if ((*buffer)[i] == '\n')
				flag = 1;
			i++;
		}
	}
	free (*buffer);
	return (bytes_read);
}

char	*get_line(int fd, char **buff, char **backup_buff)
{
	int	bytes_read;

	bytes_read = read_file(fd, buff, backup_buff);
	if (bytes_read == 0 && (*backup_buff)[0] == '\0')
	{
		free (*backup_buff);
		*backup_buff = NULL;
		return (NULL);
	}
	if (bytes_read == 0 && (*backup_buff))
		return (extract_line(backup_buff));
	if (bytes_read < 0)
	{
		free (*buff);
		return (NULL);
	}	
	return (extract_line(backup_buff));
}

char	*get_next_line(int fd)
{
	int			ret;
	char		*buff;
	char		*line;
	static char	*backup_buff;

	ret = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 256)
	{
		free_reader(&backup_buff, ret);
		return (NULL);
	}
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	if (!backup_buff)
	{
		backup_buff = (char *)malloc(BUFFER_SIZE + 1);
		if (!backup_buff)
			return (NULL);
		*backup_buff = '\0';
	}
	line = get_line (fd, &buff, &backup_buff);
	return (line);
}
