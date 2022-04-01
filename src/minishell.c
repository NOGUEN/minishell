#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
    char *line;

    signal_init();
    while (line = readline("minishell $ "))
    {
        if (*line != '\0' && !check_whitespace(line))
        {
            add_history(line);

        }
    }
}