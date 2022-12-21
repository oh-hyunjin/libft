/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 13:45:59 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/18 14:53:15 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

t_list	*find_node(int fd, t_list **head)
{
	t_list	*cur_node;
	t_list	*prev_node;
	t_list	*new;

	prev_node = NULL;
	cur_node = *head;
	while (cur_node)
	{
		if (cur_node -> fd_num == fd)
			return (cur_node);
		if (cur_node -> next == NULL)
			prev_node = cur_node;
		cur_node = cur_node -> next;
	}
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (0);
	new -> fd_num = fd;
	new -> backup = NULL;
	new -> next = NULL;
	new -> prev = prev_node;
	if (prev_node == NULL)
		return (*head = new);
	prev_node -> next = new;
	return (new);
}

char	*get_next_line(int fd)
{
	char			*read_line;
	char			*line;
	static t_list	*head;
	t_list			*node;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	node = find_node(fd, &head);
	if (!node)
		return (0);
	read_line = ft_read(fd, (char *)node -> backup);
	if (!read_line)
	{
		del_node(&head, node);
		return (NULL);
	}
	line = get_line(read_line);
	node -> backup = get_backup(read_line);
	if (node -> backup == NULL)
		del_node(&head, node);
	return (line);
}
