#include <stdio.h>
#include <string.h>

int main()
{
	char *err;

	printf("error message\n");
	for (int i = 0; i <= 106; i++)
	{
		err = strerror(i);
		printf("[%d]: %s\n", i, err);
	}
}