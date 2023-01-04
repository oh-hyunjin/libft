/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:48:50 by hyoh              #+#    #+#             */
/*   Updated: 2023/01/04 09:15:51 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>

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
	close(pipe_fd[WRITE]);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];
	t_cmd	cmd;
	int		last_status;

	if (argc < 5)
		exit(EXIT_FAILURE);
	make_proc(argc, pipe_fd, &cmd.num, &pid);
	cmd.idx = cmd.num + 1;
	if (pid == 0 && cmd.num == 1)
		first_cmd(argv[1], argv[cmd.idx], env, pipe_fd);
	else if (pid == 0 && cmd.num == argc - 3)
		last_cmd(argv[argc - 1], argv[cmd.idx], env, pipe_fd);
	waitpid(pid, &last_status, 0);
	while (wait(0) != -1);
	exit(WEXITSTATUS(last_status));
}
