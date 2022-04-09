#include "../include/minishell.h"

int get_parse_size(char *cmd, char **envp)
{
    int size;

    size = 0;
    printf("%s %d", envp[0], size);
    while (*cmd)
    {
        if (*cmd == '\'')
            size += squote_cnt(&cmd);
        if (*cmd == '\"')
            size += dquote_cnt(&cmd, envp);
    }
    return (0);
}