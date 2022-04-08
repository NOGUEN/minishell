#include "../include/minishell.h"

t_token *alloc_token(t_token *token, char **envp)
{
    int cmd_len;
    size_t  i;
    char *tmp_cmd;

    i = 0;
    while (token[i].cmd)
    {
        cmd_len = 0;
        tmp_cmd = token[i].cmd;
        cmd_len = 
    }
}