/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoh <hyoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:05:24 by hyoh              #+#    #+#             */
/*   Updated: 2022/12/21 16:58:11 by hyoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_children{
	pid_t	pidd;
	int		order;
}	t_children;

void	pipex(int argc, char **argv, t_children info)
{
	pid_t	pid;
	int		fds[2];

	printf("**** parent start ****\n");
	pipe(fds);
	for (int i = 0; i < argc - 3; i++)
	{
		pid = fork();
		if (pid == 0)
		{
			// info.pidd = pid;
			printf("\n* child start (%d)*\n", info.pidd);
			break ;	// break 안 하면 자식 프로세스가 fork함. 부모프로세스는 하나만 존재해야 한다.
		}
		if (pid != 0) // parent
		{
			info.pidd = pid;
			info.order = i;
			printf("**** (fork <%d, %d>)\n", info.pidd, info.order);
		}
	}

	if (pid == 0) // child
	{
		printf("* %d, %d\n", info.pidd, info.order);
		printf("* child end *\n\n");
	}
	else if (pid > 0) // parent
	{
		//waitpid
		printf("**** sleep~~~~\n\n");
		sleep(2);
		printf("**** parent end ****\n");
	}
}

int main(int argc, char *argv[])
{
	t_children	info;

	info.pidd = -1;
	info.order = -1;
	printf("%d\n", argc);
	pipex(argc, argv, info);
}