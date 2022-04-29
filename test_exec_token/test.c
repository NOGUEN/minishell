
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
   int fd = open("./fortest", O_RDWR | O_CREAT);
   int pid = fork();

   if (pid == 0)
   {
	   dup2(fd, 1);
	   printf("thisis test\ntestetss\ntestestests\nlastline\n");
	   close(fd);
	   exit (0);
   }
   waitpid(0, NULL, 0);
   printf("I\'m  parent");

	char buf[33];
	buf[32] = 0;
	int result = read(fd, buf,32);
	buf[result] =0;
	printf("%s", buf);





	// char * line;
	// while (line = readline("myline :"))
	// {
	// 	if (!strcmp(line, "end"))
	// 		break;
	// 	printf("read :%s\n", line);
	// 	free(line);
	// }


	return (0);
}