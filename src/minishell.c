#include "../include/minishell.h"

int main(int argc, char *argv[], char *envp[])
{
    //char *line;
    char *str = "\"hello world $ZSH\"";
    char *tmp = str;


    argc = argc * argc;
    //signal_init();
    printf("%s\n", argv[1]);
    printf("%s\n", envp[1]);
    printf("%d\n", env_len("ZSH", envp));
    //printf("%d\n", squote_cnt(&tmp));
    printf("%d", dquote_cnt(&tmp,envp));
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