#include "../include/minishell.h"

int g_exit_status;

void free_copied_env(char **copied)
{
    char **i;

    i = copied;
    while (*i)
    {
        free(*i);
        ++i;
    }
    free(copied);
}

char **copy_env(char **envp)
{
    int num_env;
    char **copied;

    num_env = -1;
    while (envp[++num_env])
        ;
    copied = malloc((num_env + 1) * sizeof(char *));
    copied[num_env] = NULL;
    for (int i = 0; i < num_env; ++i)
{        copied[i] = ft_strdup(envp[i]);
// printf("%p      \n", copied[i]);
}
    return copied;
}

int main(int argc, char *argv[], char *envp[])
{
    t_cmd *cmds;
    char *line;
    char **copied_env;

    dup2(STDIN, 100);
    dup2(STDOUT, 101);
    copied_env = copy_env(envp);
    signal_init();
    while (line = readline("minishell $ "))
    {
        if (*line != '\0' && !check_whitespace(line))
        {
            add_history(line);
            parse(&cmds, line, envp);
            // print token
            for (t_cmd *cmd = cmds; cmd; cmd = cmd->next)
            {
                for (t_token *token = cmd->tokens; token->cmd; ++token)
                    printf("token : %s \n", token->cmd);
                printf("\n");
            }
            exec(cmds, &copied_env);
            // free_list(cmds);
            free(line);
        }
    }
    free_copied_env(copied_env);
    return (0);
}
