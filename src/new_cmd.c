#include "../include/minishell.h"

t_cmd   *new_cmd(char *line, int pipe_flag, char **envp, int exit_flag)
{
    t_cmd   *result;

    printf("%d %s %d", pipe_flag, envp[0], exit_flag);
    if (!(result = (t_cmd*)malloc(sizeof(t_cmd))))
        return (NULL);
    result->cmds = split_cmd(line);
    
    return (NULL);
}