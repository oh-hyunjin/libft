#include "get_next_line.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
	FILE *fp;
	char buf[1024];

	fp = fopen("gnl", "r");
	fgets(buf, sizeof(buf), fp);
		printf("%s", buf);
	fgets(buf, sizeof(buf), fp);
		printf("%s", buf);
	printf("\n");
	fseek(fp, 0, SEEK_SET);
	fgets(buf, sizeof(buf), fp);
		printf("%s", buf);
	fgets(buf, sizeof(buf), fp);
		printf("%s", buf);
}