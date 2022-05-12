#include "../include/minishell.h"

int g_exit_status;

int main(int argc, char *argv[], char *envp[])
{
    t_cmd *cmds;
    char *line;
    char **copied_env;

    copied_env = copy_envp(envp);
    signal_init();
    while (line = readline("minishell $ "))
    {
        if (*line != '\0' && !check_whitespace(line))
        {
            add_history(line);
            parse(&cmds, line, envp);
            // print token
            // for (t_cmd *cmd = cmds; cmd; cmd = cmd->next)
            // {
            //     for (t_token *token = cmd->tokens; token->cmd; ++token)
            //         printf("token : %s \n", token->cmd);
            //     printf("\n");
            // }
            exec(cmds, &copied_env);
            // free_list(cmds);
            free(line);
        }
    }
    free_copied_env(copied_env);
    return (0);
}
