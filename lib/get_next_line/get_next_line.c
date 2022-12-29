/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 13:29:16 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/29 16:31:24 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *read_line)
{
	int		n;
	char	*line;

	if (read_line[0] == '\0')
		return (NULL);
	n = find_n(read_line);
	if (n == -1)
		line = substr(read_line, ft_strlen2(read_line));
	else
		line = substr(read_line, n + 1);
	if (!line)
		return (0);
	return (line);
}

char	*get_backup(char *read_line)
{
	int		n;
	char	*backup;

	n = find_n(read_line);
	if (n == -1)
	{
		free(read_line);
		return (NULL);
	}
	backup = substr(read_line + n + 1, ft_strlen2(read_line) - n);
	if (!backup)
	{
		free(read_line);
		return (0);
	}
	free(read_line);
	return (backup);
}

char	*ft_read(int fd, char *backup)
{
	int		size;
	char	*buf;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		free(backup);
		return (0);
	}
	size = 1;
	while (find_n(backup) == -1 && size > 0)
	{
		size = read(fd, buf, BUFFER_SIZE);
		if (size == -1)
		{
			free(backup);
			free(buf);
			return (NULL);
		}
		buf[size] = '\0';
		backup = ft_strjoin2(backup, buf);
	}
	free(buf);
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*read_line;
	char		*line;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	read_line = ft_read(fd, backup);
	if (!read_line)
		return (NULL);
	line = get_line(read_line);
	backup = get_backup(read_line);
	return (line);
}
