/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:48:50 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/29 13:49:02 by hyoh             ###   ########.fr       */
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
		if (after[i][0] == '\'')
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

void	first_cmd(char *file, char *argv_cmd, char **env, int pipe_fd[])
{
	int		infile_fd;
	char	**cmd;
	char	*path;

	printf("argv : %s\n", argv_cmd);
	close(pipe_fd[READ]);
	infile_fd = open(file, O_RDWR, 0644);
	if (infile_fd < 0)
		error_exit(1);
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

	printf("argv : %s\n", argv_cmd);
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

	printf("argv : %s\n", argv_cmd);
	close(pipe_fd[OLD][WRITE]);
	close(pipe_fd[NEW][READ]);
	cmd = parse_cmd(argv_cmd);
	path = get_path(cmd[0], env);
	dup2(pipe_fd[OLD][READ], 0);
	dup2(pipe_fd[NEW][WRITE], 1);
	execve(path, cmd, env);
	error_exit(127);
}

void	make_proc(int last_cmd_num, int pipe_fd[2][2], int *cmd_num, int *pid)
{
	*cmd_num = 0;
	while (++(*cmd_num) <= last_cmd_num)
	{
		if (pipe_fd[OLD][READ] != -2)
		{
			// close old
			close(pipe_fd[OLD][READ]);
			close(pipe_fd[OLD][WRITE]); // 안하면 무한로딩
		}
		if (*cmd_num != 1)
		{
			// old = new
			pipe_fd[OLD][READ] = pipe_fd[NEW][READ];
			pipe_fd[OLD][WRITE] = pipe_fd[NEW][WRITE];
		}
		if (*cmd_num != last_cmd_num && pipe(pipe_fd[NEW]) < 0)
			error_exit(3);
		*pid = fork();
		if (*pid < 0)
			error_exit(2);
		else if (*pid == 0)
		{
			printf("%d forked\n", *cmd_num);
			return ;
		}
	}
	// close last old
	close(pipe_fd[OLD][READ]);
	close(pipe_fd[OLD][WRITE]); // 안하면 무한로딩
}

void	pipex_init(int argc, char **argv, int *hd_flag, int pipe_fd[2][2])
{
	if (argv[1] == NULL)
		exit(EXIT_FAILURE);
	*hd_flag = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		*hd_flag = 1;
	if (*hd_flag == 0 && argc < 5)
		exit(EXIT_FAILURE);
	else if (*hd_flag == 1 && argc < 6)
		exit(EXIT_FAILURE);
	pipe_fd[0][0] = -2;
	pipe_fd[0][1] = -2;
	pipe_fd[1][0] = -2;
	pipe_fd[1][1] = -2;
}
//cmd : 0부터 시시작작하하기

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		pipe_fd[2][2];
	int		hd_flag;
	t_cmd	cmd;
	int		last_status;

	pipex_init(argc, argv, &hd_flag, pipe_fd);
	make_proc(argc - 3 - hd_flag, pipe_fd, &cmd.num, &pid);
	cmd.idx = cmd.num + 1 + hd_flag;
	printf("\ncmd.idx :  %d\n", cmd.idx);
	if (pid == 0 && cmd.num == 1)
	{
		printf("[first cmd]\n");
		first_cmd(argv[1], argv[cmd.idx], env, pipe_fd[NEW]); // new만 사용
	}
	else if (pid == 0 && cmd.num == argc - 4)
	{
		printf("[last cmd]\n");
		last_cmd(argv[argc - 1], argv[cmd.idx], env, pipe_fd[OLD]); // old만 사용
	}
	else if (pid == 0)
	{
		printf("[other cmd]\n");
		other_cmd(argv[cmd.idx], env, pipe_fd); // new, old 둘 다 사용
	}
	waitpid(pid, &last_status, 0);
	while (wait(0) != -1); // 0넣어서 변수 없애도 되나
	exit(WEXITSTATUS(last_status));
}
