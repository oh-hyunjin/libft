/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:14:31 by hyoh              #+#    #+#             */
/*   Updated: 2023/01/04 13:52:09 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error_exit(char *exe_file, char *cmd, int num) // 마지막 에러만 출력..???
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

char	*find_in_env(t_info info, char **paths, char *cmd)
{
	char	*slash_cmd;
	char	*true_path;
	int		i;

	if (paths == NULL)
		exit(EXIT_FAILURE);
	slash_cmd = ft_strjoin("/", cmd);
	i = -1;
	while (paths[++i] != NULL)
	{
		true_path = ft_strjoin(paths[i], slash_cmd);
		if (!true_path)
		{
			double_free(paths, i);
			exit(EXIT_FAILURE);
		}
		if (access(true_path, X_OK) == 0)
			return (true_path);
		free(true_path);
	}
	free(slash_cmd);
	double_free(paths, i);
	error_exit(info.exe_file, cmd, 127);
	return (0);
}

char	*get_path(t_info info, char *cmd)
{
	int	i;

	if (cmd == NULL)
		error_exit(info.exe_file, cmd, 127);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	i = -1;
	while (info.env[++i] != NULL)
		if (ft_strnstr(info.env[i], "PATH=", 10) != NULL)
			break ;
	if (info.env[i] == NULL)
		exit(EXIT_FAILURE);
	return (find_in_env(info, ft_split(info.env[i] + 5, ':'), cmd));
}

char	**parse_cmd(char *before)
{
	char	**after;
	char	*s_quote;
	int		quote_flag;
	int		i;

	s_quote = before;
	after = ft_split(before, ' ');
	if (!after)
		exit(EXIT_FAILURE);
	i = -1;
	quote_flag = 0;
	while (after[++i] != NULL)
	{
		if (after[i][0] == '\'' || after[i][0] == '\"')
		{
			quote_flag = 1;
			after[i] = ft_substr(s_quote, 1, ft_strlen(s_quote) - 2);
			// free;
			continue ;
		}
		if (quote_flag == 1)
		{
			after[i] = NULL;
			free(after[i]);
		}
		else
			s_quote += (ft_strlen(after[i]) + 1);
	}
	return (after);
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
	while(1)
	{
		write(1, "here_doc) ", 10);
		temp = get_next_line(0);
		if (temp == NULL)
			exit(EXIT_FAILURE);
		if (ft_strncmp(temp, limiter, ft_strlen(temp)) == 0) // strlen에 limiter 놔야 되는지..
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
	info->exe_file = ft_strrchr(info->argv[0], '/') + 1; // 없으면 널리턴????
	if (info->exe_file == NULL)
		info->exe_file = info->argv[0];
	info->outfile = info->argv[info->argc - 1];
	info->hd.fd = -2;
	info->hd.flag = 0;
	if (ft_strncmp(info->argv[1], "here_doc", 8) == 0)
		get_heredoc(info->argv, &info->hd);
	if (info->hd.flag == 0 && info->argc < 5)
		exit(EXIT_FAILURE);
	else if (info->hd.flag == 1 && info->argc != 6)
		exit(EXIT_FAILURE);
	*cmd_last = info->argc - 4 - info->hd.flag;
	pipe_fd[0][0] = -2;/////////
	pipe_fd[0][1] = -2;
	pipe_fd[1][0] = -2;
	pipe_fd[1][1] = -2;
}
