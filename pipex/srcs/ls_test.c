#include "../includes/minishell.h"


int main()
{
	int		pid;
	int		ls_pipe[2];

	pid = fork();
	if (pid == CHILD)
	{

		execve("ls_grep.sh", arg, NULL);
	}
	waitpid(CHILD, NULL, 0);
	return ;
}
