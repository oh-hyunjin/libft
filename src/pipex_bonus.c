/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:48:50 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/29 17:04:01 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <string.h>

void	error_exit(int num)
{
	if (num == 1)
		write(2, "file open fail\n", 15);
	else if (num == 2)
		write(2, "fork fail\n", 10);
	else if (num == 3)
		write(2, "pipe fail\n", 10);
	else if (num == 127)
	{
		write(2, "command not found\n", 18);
		exit(127);
	}
	exit(1);
}

char	*get_path(char *cmd, char **env)
{
	char	*needle;
	char	**paths;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (*env != NULL)
	{
		needle = ft_strnstr(*env, "PATH=", 10); // 10?
		if (needle != NULL)
			break ;
		env++;
	}
	needle += 5;
	paths = ft_split(needle, ':'); // free
	while (*paths != NULL)
	{
		*paths = ft_strjoin(*paths, ft_strjoin("/", cmd));
		if (access(*paths, X_OK) == 0)
			break ;
		paths++;
	}
	return (*paths);
}

char	**parse_cmd(char *before)
{
	char	**after;
	char	*s_quote;
	int		quote_flag;
	int		i;

	s_quote = before;
	after = ft_split(before, ' ');
	i = -1;
	quote_flag = 0;
	while (after[++i] != NULL)
	{
		if (after[i][0] == '\'' || after[i][0] == '\"')
		{
			quote_flag = 1;
			after[i] = ft_substr(s_quote, 1, ft_strlen(s_quote) - 2);
			continue ;
		}
		if (quote_flag == 1)
			after[i] = NULL; //free(after[i]);????
		else
			s_quote += (ft_strlen(after[i]) + 1);
	}
	return (after);
}

void	first_cmd(char *file, char *argv_cmd, char **env, int pipe_fd[], int hd)
{
	int		infile_fd;
	char	**cmd;
	char	*path;

	// printf("argv : %s\n", argv_cmd);
	close(pipe_fd[READ]);
	if (hd != -2)
		infile_fd = hd;
	else
	{
		infile_fd = open(file, O_RDWR, 0644);
		if (infile_fd < 0)
			error_exit(1);
	}

	cmd = parse_cmd(argv_cmd);
	path = get_path(cmd[0], env);
	dup2(infile_fd, 0);
	dup2(pipe_fd[WRITE], 1);
	execve(path, cmd, env);
	error_exit(127);
}

void	last_cmd(char *file, char *argv_cmd, char **env, int pipe_fd[])
{
	int		outfile_fd;
	char	**cmd;
	char	*path;

	// printf("argv : %s\n", argv_cmd);
	close(pipe_fd[WRITE]);
	outfile_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
		error_exit(1);
	cmd = parse_cmd(argv_cmd);
	path = get_path(cmd[0], env);
	dup2(pipe_fd[READ], 0);
	dup2(outfile_fd, 1);
	execve(path, cmd, env);
	error_exit(127);
}

void	other_cmd(char *argv_cmd, char **env, int pipe_fd[2][2])
{
	char	**cmd;
	char	*path;

	// printf("argv : %s\n", argv_cmd);
	close(pipe_fd[OLD][WRITE]);
	close(pipe_fd[NEW][READ]);
	cmd = parse_cmd(argv_cmd);
	path = get_path(cmd[0], env);
	dup2(pipe_fd[OLD][READ], 0);
	dup2(pipe_fd[NEW][WRITE], 1);
	execve(path, cmd, env);
	error_exit(127);
}

void	make_proc(int cmd_last, int pipe_fd[2][2], int *cmd_cur, int *pid)
{
	*cmd_cur = -1;
	while (++(*cmd_cur) <= cmd_last)
	{
		if (pipe_fd[OLD][READ] != -2) // close old
			(close(pipe_fd[OLD][READ]), close(pipe_fd[OLD][WRITE]));
		if (*cmd_cur != 0)
		{
			// old = new
			pipe_fd[OLD][READ] = pipe_fd[NEW][READ];
			pipe_fd[OLD][WRITE] = pipe_fd[NEW][WRITE];
		}
		if (*cmd_cur != cmd_last && pipe(pipe_fd[NEW]) < 0)
			error_exit(3);
		*pid = fork();
		if (*pid < 0)
			error_exit(2);
		else if (*pid == 0)
			return ;
	}
	// close last old
	(close(pipe_fd[OLD][READ]), close(pipe_fd[OLD][WRITE])); // 안하면 무한로딩
}

int	get_heredoc(char **argv, t_hd *hd)
{
	char	*limiter;
	char	*temp;

	hd->flag = 1;
	hd->fd = 0;
	limiter = ft_strjoin(argv[2], "\n");
	printf("limiter : %s\n", limiter);
	printf("open : %d\n", hd->fd = open("tmp", O_RDWR | O_CREAT | O_TRUNC, 0644));
	while(1)
	{
		write(1, "here_doc) ", 10);
		temp = get_next_line(0);
		if (ft_strncmp(temp, limiter, ft_strlen(temp)) == 0) // strlen에 limiter 놔야 되는지..
			break ;
		write(hd->fd, temp, ft_strlen(temp));
	}
	return (0);
}

void	pipex_init(int argc, char **argv, t_hd *hd, int pipe_fd[2][2], int *cmd_last)
{
	if (argv[1] == NULL)
		exit(EXIT_FAILURE);
	hd->fd = -2;
	hd->flag = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		get_heredoc(argv, hd);
	if (hd->flag == 0 && argc < 5)
		exit(EXIT_FAILURE);
	else if (hd->flag == 1 && argc < 6)
		exit(EXIT_FAILURE);
	*cmd_last = argc - 4 - hd->flag;
	pipe_fd[0][0] = -2;
	pipe_fd[0][1] = -2;
	pipe_fd[1][0] = -2;
	pipe_fd[1][1] = -2;
}
//cmd : 0부터 시작하하기

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		pipe_fd[2][2];
	t_hd	hd;
	t_cmd	cmd;
	int		last_status;

	pipex_init(argc, argv, &hd, pipe_fd, &cmd.last);
	make_proc(argc - 4 - hd.flag, pipe_fd, &cmd.cur, &pid);
	cmd.idx = cmd.cur + 2 + hd.flag;

	if (pid == 0 && cmd.cur == 0)
	{
		// printf("[first cmd]\n");
		first_cmd(argv[1], argv[cmd.idx], env, pipe_fd[NEW], hd.fd); // new만 사용
	}
	else if (pid == 0 && cmd.cur == argc - 4 - hd.flag)
	{
		// printf("[last cmd]\n");
		last_cmd(argv[argc - 1], argv[cmd.idx], env, pipe_fd[OLD]); // old만 사용
	}
	else if (pid == 0)
	{
		// printf("[other cmd]\n");
		other_cmd(argv[cmd.idx], env, pipe_fd); // new, old 둘 다 사용
	}
	waitpid(pid, &last_status, 0);
	while (wait(0) != -1); // 0넣어서 변수 없애도 되나
	close(hd.fd);
	exit(WEXITSTATUS(last_status));
}
