#include <unistd.h>

int main(int argc, char **argv)
{
	execve("/bin/ls", argv, NULL);
	return (0);
}