#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define READ 0
#define WRITE 1

int main(int argc, char **argv)
{
	int		fds[2];
	int		file1_fd;
	int		file2_fd;
	pid_t	*pids;
	pid_t	pid;
	int		current_num;

	printf("========= [P] parent process start =========\n");
	pids = (pid_t *)malloc(sizeof(pid_t) * argc - 3);
	for (int i = 0; i < argc -3; i++)
		pids[i] = -2;
	current_num = -1;
	pipe(fds);
	
	while (++current_num < argc -3)
	{
		pid = fork();
		printf("(fork %d)\n", pid);
		if (pid == -1)
		{
			printf("fork error!\n");
			exit(0);
		}
		if (pid == 0) // 자식 프로세스면 손주 프로세스 만들지 않게 끝내기
		{
			printf("\n----- [%d] child process start -----\n", current_num);
			break ;
		}
		if (pid != 0) // fork를 끝낸 후의 부모 프로세스 (pid = 방금 생성한 자식pid)
		{
			pids[current_num] = pid;
			printf("[P] forked <%d : %d>\n", current_num, pid);
		}
	}

	if (pid == 0)
	{
		printf("[%d] running process id : %d> \n", current_num, getpid());
		
		// 첫번째 자식이면
		if (current_num == 0)
		{
			file1_fd = open("file1.txt", O_RDWR, 0644);
			printf("[%d] file1 open (fd : %d)\n", current_num, file1_fd);
			dup2(file1_fd, 0);
			dup2(fds[WRITE], 1);
			printf("ddd");
			close(file1_fd);
			printf("\n-----  [%d] child process start  -----\n", current_num);
		}

		// 마지막 자식이면
		else if (current_num == argc - 4)
		{
			file2_fd = open("file2.txt", O_RDWR, 0644);
			printf("[%d] file2 open (fd : %d)\n", current_num, file2_fd);
			dup2(fds[READ], 0);
			dup2(file2_fd, 1);
			close(file2_fd);
			// printf("\n----- [%d] child process end  -----\n", current_num);
		}

		// 중간 자식이면
		else
		{
			dup2(fds[READ], 0);
			dup2(fds[WRITE], 1);
			printf("-----  [%d] child process end  -----\n\n", current_num);
		}
	}
	if (pid != 0)
	{
		sleep(3); // wait으로 고치기
		printf("=========  [P] parent process end  =========\n\n");
		for(int i = 0; i < current_num; i++)
			printf("%d : %d\n", i, pids[i]);
		exit(0);
	}
}