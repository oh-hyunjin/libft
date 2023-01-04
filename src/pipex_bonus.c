/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:48:50 by hyoh              #+#    #+#             */
/*   Updated: 2023/01/04 13:29:06 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_cmd(t_info info, char *argv_cmd, int pipe_fd[])
{
	char	*file;
	int		infile_fd;
	char	**cmd;
	char	*path;

	close(pipe_fd[READ]);
	cmd = parse_cmd(argv_cmd);
	path = get_path(info, cmd[0]);
	file = info.argv[1];
	if (info.hd.flag != 0)
		file = "tmp";
	infile_fd = open(file, O_RDWR, 0644);
	if (infile_fd < 0)
		error_exit(info.exe_file, file, 1);
	dup2(infile_fd, 0);
	dup2(pipe_fd[WRITE], 1);
	execve(path, cmd, info.env);
	error_exit(info.exe_file, cmd[0], 127);
}

void	last_cmd(t_info info, char *argv_cmd, int pipe_fd[])
{
	int		outfile_fd;
	char	**cmd;
	char	*path;

	close(pipe_fd[WRITE]);
	if (info.hd.flag == 0)
		outfile_fd = open(info.outfile, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		outfile_fd = open(info.outfile, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (outfile_fd < 0)
		error_exit(info.exe_file, info.outfile, 1);
	cmd = parse_cmd(argv_cmd);
	path = get_path(info, cmd[0]);
	dup2(pipe_fd[READ], 0);
	dup2(outfile_fd, 1);
	execve(path, cmd, info.env);
	error_exit(info.exe_file, cmd[0], 127);
}

void	other_cmd(t_info info, char *argv_cmd, int pipe_fd[2][2])
{
	char	**cmd;
	char	*path;

	close(pipe_fd[OLD][WRITE]);
	close(pipe_fd[NEW][READ]);
	cmd = parse_cmd(argv_cmd);
	path = get_path(info, cmd[0]);
	dup2(pipe_fd[OLD][READ], 0);
	dup2(pipe_fd[NEW][WRITE], 1);
	execve(path, cmd, info.env);
	error_exit(info.exe_file, cmd[0], 127);
}

void	make_proc(int pipe_fd[2][2], t_cmd *cmd, int *pid)
{
	cmd->cur = -1;
	while (++(cmd->cur) <= cmd->last)
	{
		if (pipe_fd[OLD][READ] != -2)
			(close(pipe_fd[OLD][READ]), close(pipe_fd[OLD][WRITE]));
		if (cmd->cur != 0)
		{
			pipe_fd[OLD][READ] = pipe_fd[NEW][READ];
			pipe_fd[OLD][WRITE] = pipe_fd[NEW][WRITE];
		}
		if (cmd->cur != cmd->last && pipe(pipe_fd[NEW]) < 0)
			exit(EXIT_FAILURE);
		*pid = fork();
		if (*pid < 0)
			exit(EXIT_FAILURE);
		else if (*pid == 0)
			return ;
	}
	(close(pipe_fd[OLD][READ]), close(pipe_fd[OLD][WRITE]));
}

int	main(int argc, char **argv, char **env)
{
	t_info	info;
	pid_t	pid;
	t_cmd	cmd;
	int		pipe_fd[2][2];
	int		status;

	info.argc = argc;
	info.argv = argv;
	info.env = env;
	pipex_init(&info, pipe_fd, &cmd.last);
	make_proc(pipe_fd, &cmd, &pid);
	cmd.idx = cmd.cur + 2 + info.hd.flag;
	if (pid == 0 && cmd.cur == 0)
		first_cmd(info, argv[cmd.idx], pipe_fd[NEW]);
	else if (pid == 0 && cmd.cur == argc - 4 - info.hd.flag)
		last_cmd(info, argv[cmd.idx], pipe_fd[OLD]);
	else if (pid == 0)
		other_cmd(info, argv[cmd.idx], pipe_fd);
	waitpid(pid, &info.last_status, 0);
	while (wait(&status) != -1)
		continue ;
	if (info.hd.flag != 0)
		unlink("tmp");
	exit(WEXITSTATUS(info.last_status));
}
