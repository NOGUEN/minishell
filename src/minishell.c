#include "../include/minishell.h"

int main(int argc, char *argv[], char *envp[])
{
    //char *line;

    argc = argc * argc;
    //signal_init();
    printf("%s", argv[1]);
    printf("%s", envp[1]);
    /*
    while (line = readline("minishell $ "))
    {
        if (*line != '\0' && !check_whitespace(line))
        {
            add_history(line);

        }
    }
    */
}