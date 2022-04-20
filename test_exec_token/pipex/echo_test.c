#include <stdio.h>
#include <unistd.h>


int main(int argc, char **argv)
{
	printf(" hi %s\n", argv[3]);
//	execve(argv[0], argv+1, NULL);
	//second parameter of execve is same with command line entering on shell prompt, 
	//the input file by < or << is written on STDIN before exececuting command
	return 0;
}
