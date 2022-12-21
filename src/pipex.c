/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 13:41:17 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/21 12:42:19 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parsing_errorcheck(int argc, char **argv) // 굳이 파싱 안 해도 될듯..
{
	char	*infile;
	// infile
	infile = *argv;
	ft_printf("infile: %s\n", infile);

	// cmd
	while (--argc != 0)
	{
		ft_printf("%s\n", *argv);
	}

	// outfile
	ft_printf("outfile: %s\n", *argv);

	return (0);
}

int	pipex(int cmd_num, char **argv)
{
	pid_t	pid;
	int		fds[2]; // old, new??????

	pipe(fds);
	pid = fork();
	if (pid == -1)
		return (-1);

	// 부모 프로세스라면
	if (pid != 0)
	{
		printf("<parent process start>\n");
		while (cmd_num-- != 1/* cmd 개수-1만큼 */)
		{
			fork();
		}
		wait();
		printf("<parent process end>\n");
	}

	// 자식 프로세스라면
	if (pid == 0)
	{
		printf("<child process start>\n");
		if (is1stCmd)
		{
			open file1 with 0_CREAT option;
			dup2(file1, stdin);
			close(file1);
			dup2(fds[WRITE], stdout);
		}
		else if (isLastCmd)
		{
			open file1 with 0_CREAT option;
			dup2(fds[READ], stdin);
			dup2(fds[WRITE], file2);
			close(file2);
		}
		else
		{
			dup2(fds[READ], stdin);
			dup2(fds[WRITE], stdout);
		}
		access();
		execve();
		printf("<child process end>\n");
	}
}

int main(int argc, char *argv[])
{
	ft_printf("%d\n", argc);
	if (parsing_errorcheck(argc, ++argv) == -1)
		return (0);
	pipex(argc - 2, argv);
}