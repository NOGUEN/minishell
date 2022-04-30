
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
   int fd = open("./fortes", O_RDWR | O_APPEND);
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
   close(fd);

	fd = open("./fortes", O_RDWR );

	char buf[1025];
	buf[1024] = 0;
	int result = read(fd, buf,1024);
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
	//

	close(fd);
	return (0);
}
