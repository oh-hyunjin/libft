/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:48:50 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/27 16:26:23 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
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

	while(*env != NULL)
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
	return(*paths);
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

void	other_cmd(char *argv_cmd, char **env, int pipe_fd[])
{
	char	**cmd;
	char	*path;

	cmd = parse_cmd(argv_cmd);
	path = get_path(cmd[0], env);
	dup2(pipe_fd[READ], 0);
	dup2(pipe_fd[WRITE], 1);
	execve(path, cmd, env);
	error_exit(127);
}

void	make_proc(int argc, int pipe_fd[], int *cmd_num, int *pid)
{
	*cmd_num = 0;

	while (++(*cmd_num) != argc - 2)
	{
		if (*cmd_num != argc - 3 && pipe(pipe_fd) < 0)
			error_exit(3);
		*pid = fork();
		if (*pid < 0)
			error_exit(2);
		else if (*pid == 0)
			break ;
	}
}

void	pipex_init(int argc, char **argv, int *hd_flag)
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
}

int main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		cmd_num;
	int		hd_flag;
	int		cmd_idx;

	pipex_init(argc, argv, &hd_flag);
	make_proc(argc, pipe_fd, &cmd_num, &pid);

	cmd_idx = cmd_num + 1 + hd_flag;
	if (pid == 0 && cmd_num == 1)
		first_cmd(argv[1], argv[cmd_idx], env, pipe_fd);
	else if (pid == 0 && cmd_num == argc - 3)
		last_cmd(argv[argc - 1], argv[cmd_idx], env, pipe_fd);
	// else if (pid == 0)
	// 	other_cmd(argv[cmd_idx], env, pipe_fd);

	int		wait_status;
	int		last_status;
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]); // 안하면 무한로딩
	waitpid(pid, &last_status, 0);
	while (wait(&wait_status) != -1); // 0넣어서 변수 없애도 되나
	exit(WEXITSTATUS(last_status));
}
