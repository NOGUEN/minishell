#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int fd = open("./fortest", O_RDWR | O_CREAT);
    int pid = fork();

    if (pid == 0)
    {
        printf("hi\n");
        return (0);
    }
    waitpid(0, NULL, 0);
    printf("I'm  parent");
    return (0);
}