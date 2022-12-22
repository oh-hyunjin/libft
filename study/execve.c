#include <unistd.h>
#include <stdio.h>
#include <unistd.h>

void run()
{
	char *pathname = "bin/ls";
	int mode = R_OK | W_OK;
	if( access( pathname, mode ) == 0 ){
		printf("읽고 쓸 수 있습니다.");
	}
	else{
		printf("권한이 없거나 존재하지 않습니다.");
	}

	char *argv[]={"/bin/ls", NULL};
	execve("/bin/ls", argv, NULL);
}

int main(int argc, char **argv)
{
	run();
	return (0);
}