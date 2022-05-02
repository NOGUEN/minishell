#include "../include/minishell.h"

int get_parse_size(char *cmd, char **envp)
{
    int size;
    char *tmp;

    size = 0;
    while (*cmd)
    {
        if (*cmd == '\'')
            size += squote_cnt(&cmd);
        else if (*cmd == '\"')
            size += dquote_cnt(&cmd, envp);
        else if (*cmd == '$')
        {
            ++cmd;
            tmp = cut_string(&cmd);
            size += env_len(tmp, envp);
        }
        ++cmd;
    }
    return (size);
}