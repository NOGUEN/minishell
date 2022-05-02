#include "../include/minishell.h"

int g_exit_status = 0;

int main(int argc, char *argv[], char *envp[])
{
    t_cmd *cmds;
    char *line;
    while (line = readline("minishell $ "))
    {
        if (*line != '\0' && !check_whitespace(line))
        {
            add_history(line);
            parse(&cmds, line, envp);
            int i = -1;
			
            printf("\n\n\n");
			while (cmds->cmd_line[++i].cmd != NULL)
			{
				printf("cmd : %s\n", cmds->cmd_line[i].cmd);
				printf("redir_flag : %d\n", cmds->cmd_line[i].redir_flag);
				printf("exit_flag : %d\n", cmds->exit_flag);
				printf("index : %d\n", i);
			}
            
            if (cmds->next != NULL)
            {
                i = -1;
                while (cmds->next->cmd_line[++i].cmd != NULL)
			    {
		    		printf("cmd : %s\n", cmds->cmd_line[i].cmd);
	    			printf("redir_flag : %d\n", cmds->cmd_line[i].redir_flag);
    				printf("exit_flag : %d\n", cmds->exit_flag);
				    printf("index : %d\n", i);
			    }
            }
        }
    }
}