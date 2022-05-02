#include "../include/minishell.h"

t_cmd   *new_cmd(char *line, int pipe_flag, char **envp, int exit_flag)
{
    t_cmd   *result;

    if (!(result = (t_cmd*)malloc(sizeof(t_cmd))))
        return (NULL);
    result->cmd_line = split_cmd(line);
    alloc_token(result->cmd_line, envp);
    result->pipe_flag = pipe_flag;
    if (exit_flag == 0 && pipe_flag == 0)
        result->exit_flag = 1;
    else
        result->exit_flag = 0;
    result->next = NULL;
    return (result);
}