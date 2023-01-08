/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:14:31 by hyoh              #+#    #+#             */
/*   Updated: 2023/01/08 14:00:49 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_exit(char *exe_file, char *cmd, int num)
{
	write(2, exe_file, ft_strlen(exe_file));
	write(2, ": ", 2);
	write(2, cmd, ft_strlen(cmd));
	if (num == 1)
		write(2, ": No such file or directory\n", 28);
	else if (num == 127)
	{
		write(2, ": command not found\n", 20);
		exit(127);
	}
	exit(1);
}

void	double_free(char **target, int num)
{
	while (--num != -1)
		free(target[num]);
	free(target);
}

int	get_heredoc(char **argv, t_hd *hd)
{
	char	*limiter;
	char	*temp;

	hd->flag = 1;
	hd->fd = 0;
	limiter = ft_strjoin(argv[2], "\n");
	if (limiter == NULL)
		exit(EXIT_FAILURE);
	hd->fd = open("tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (hd->fd < 0)
		exit(EXIT_FAILURE);
	while (1)
	{
		write(1, "here_doc) ", 10);
		temp = get_next_line(0);
		if (temp == NULL)
			exit(EXIT_FAILURE);
		if (ft_strncmp(temp, limiter, ft_strlen(temp)) == 0)
			break ;
		write(hd->fd, temp, ft_strlen(temp));
	}
	close(hd->fd);
	return (0);
}

void	pipex_init(t_info *info, int pipe_fd[2][2], int *cmd_last)
{
	if (info->argv[1] == NULL)
		exit(EXIT_FAILURE);
	info->exe_file = ft_strrchr(info->argv[0], '/') + 1;
	if (info->exe_file == NULL)
		info->exe_file = info->argv[0];
	info->outfile = info->argv[info->argc - 1];
	info->hd.fd = -2;
	info->hd.flag = 0;
	if (ft_strncmp(info->argv[1], "here_doc", 8) == 0)
	{
		if (info->argc != 6)
			exit(EXIT_FAILURE);
		get_heredoc(info->argv, &info->hd);
	}
	if (info->hd.flag == 0 && info->argc < 5)
		exit(EXIT_FAILURE);
	*cmd_last = info->argc - 4 - info->hd.flag;
	pipe_fd[OLD][READ] = -2;
	pipe_fd[OLD][WRITE] = -2;
	pipe_fd[NEW][READ] = -2;
	pipe_fd[NEW][WRITE] = -2;
}
