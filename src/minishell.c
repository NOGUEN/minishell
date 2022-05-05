#include "../include/minishell.h"

int g_exit_status = 0;

int main(int argc, char *argv[], char *envp[])
{
    t_cmd   *cmds;
    char    *line;

    while (line = readline("minishell $ "))
    {
        if (*line != '\0' && !check_whitespace(line))
        {
            add_history(line);
            parse(&cmds, line, envp);


            // command test

			// print token
			for (t_cmd *cmd = cmds; cmd; cmd = cmd->next)
			{
				for (t_token*token = cmd->cmd_line;token->cmd;++token)
					printf("token : %s \n", token->cmd);
				printf("\n");
			}

            
            exec(cmds, envp);
            // free_list(cmds);						  
            free(line);				
        }
    }
}
