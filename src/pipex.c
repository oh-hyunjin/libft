/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:48:50 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/29 12:12:28 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>

void	error_exit(int num)
{
	if (num == 1)
		write(2, "pipex: input: No such file or directory\n", 40);
	else if (num == 2)
		write(2, "fork fail\n", 10);
	else if (num == 3)
		write(2, "pipe fail\n", 10);
	else if (num == 127)
	{
		write(2, "pipex: fizzBuzz: command not found\n", 35);
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
	if (paths == NULL)
		return (0);
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

void	make_proc(int argc, int pipe_fd[2], int *cmd_num, int *pid)
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
			return ;
	}
	close(pipe_fd[READ]);
	close(pipe_fd[WRITE]); // 안하면 무한로딩
}

void	pipex_init(int argc, char **argv)
{
	if (argv[1] == NULL)
		exit(EXIT_FAILURE);
	if (argc < 5)
		exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];
	t_cmd	cmd;
	int		last_status;

	pipex_init(argc, argv);
	make_proc(argc, pipe_fd, &cmd.num, &pid);
	cmd.idx = cmd.num + 1;
	if (pid == 0 && cmd.num == 1)
		first_cmd(argv[1], argv[cmd.idx], env, pipe_fd);
	else if (pid == 0 && cmd.num == argc - 3)
		last_cmd(argv[argc - 1], argv[cmd.idx], env, pipe_fd);
	waitpid(pid, &last_status, 0);
	while (wait(0) != -1); // wait_status 말고 0넣어서 변수 없애도 되나
	exit(WEXITSTATUS(last_status));
}
