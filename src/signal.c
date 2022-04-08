#include "../include/minishell.h"

void    signal_sigint(int signo)
{
    pid_t   pid;
    int     status;

    pid = waitpid(-1, &status, WNOHANG);
    pid = pid * 1;
    if (signo == SIGINT)
    {
        //not complete yet
    }
}

void    signal_sigquit(int signo)
{
    pid_t   pid;
    int     status;


    pid = waitpid(-1, &status, WNOHANG);
    pid = pid * 1;
    if (signo == SIGQUIT)
    {
        //not complete yet
    }
}

void    signal_init(void)
{
    signal(SIGINT, signal_sigint);
    signal(SIGQUIT, signal_sigquit);
}