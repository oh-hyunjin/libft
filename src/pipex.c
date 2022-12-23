/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 17:48:50 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/23 14:13:41 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit()
{
	printf("error\n");
	exit(0);
}

char	*get_path(char *argv, char *cmd, char **env) // 삼중 포인터..
{
	char	*needle;
	char	**paths;

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
	if (paths == NULL)
		error_exit();
	return(*paths);
}

void	first_cmd(char *argv, char **env, int fds[])
{
	int		infile_fd;
	char	**split_cmd; // malloc?
	char	*path;

	close(fds[0]);
	infile_fd = open("infile", O_RDWR, 0644);
	if (infile_fd < 0)
		error_exit();

	split_cmd = ft_split(argv, ' '); // free하기
	path = get_path(argv, split_cmd[0], env);
	dup2(infile_fd, 0);
	dup2(fds[1], 1);
	execve(path, split_cmd, NULL); //env넣기
	exit(127);
}

void	last_cmd(char *argv, int fds[])
{
	int		outfile_fd;
	char	**argv_cmd;
	char	**paths;

	usleep(100); //sleep이랑 차이점
	close(fds[1]);
	printf("\nlast child prcoess start\n");
	outfile_fd = open("outfile", O_RDWR, 0644);
	if (outfile_fd < 0)
		error_exit();
	printf("[ fd ] : %d\n", outfile_fd);

	// path argv
	argv_cmd = ft_split(argv, ' '); // free하기
	int i = 0;
	printf("[argv] : ");
	while (argv_cmd[i] != NULL)
		printf("%s\n", argv_cmd[i++]);
	// parse path
	paths = ft_split("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki", ':'); // free
	for (int i = 0; i < 10; i++)
	{
		*paths = ft_strjoin(*paths, ft_strjoin("/", argv_cmd[0]));
		if (access(*paths, X_OK) == 0)
		{
			printf("[PATH] : %s\n", *paths);
			break ;
		}
		paths++;
	}

	dup2(fds[0], 0);
	dup2(outfile_fd, 1);
	execve(*paths, argv_cmd, NULL);
	exit(127);
}

void	parent()
{
	// int		wait_status;

	// while(wait(&wait_status) != -1);
	exit(0);
}

void	make_proc(int argc, int fds[], int *current, int *pid)
{
	if (pipe(fds) < 0)
		error_exit();
	printf("fds : [%d] [%d]\n", fds[0], fds[1]);
	while (++(*current) != argc - 3)
	{
		*pid = fork();
		if (*pid < 0)
			error_exit();
		else if (*pid == 0)
			break ;
	}
}

int main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		fds[2];
	int		current;

	current = -1;
	printf("start\n");

	make_proc(argc, fds, &current, &pid);
	if (pid == 0 && current == 0)
		first_cmd(argv[current + 2], env, fds);
	else if (pid == 0 && current == argc - 4)
		last_cmd(argv[current + 2], fds);
	else if (pid != 0)
		parent();
}
