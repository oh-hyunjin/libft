#include <stdio.h>
#include <unistd.h>

int main()
{
	if (!access("test.txt", F_OK))
		printf("File exists\n");
	else 
		printf("File doesn't exist\n");
	
	if (!access("test.txt", X_OK))
		printf("File is executable\n");
	else
		printf("File is not executable\n");
}