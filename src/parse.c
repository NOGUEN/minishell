#include "../include/minishell.h"

void    parse(t_cmd **cmds, char *line, char **envp)
{
    int index;
    int begin;
    int flag;
    t_cmd   *new;
    t_cmd   *tmp;

    index = 0;
    begin = 0;
    flag = PIPE;
    if ((line[index] == '\"' || line[index] == '\'') && (flag & QUOTE) == 0)
        flag |= QUOTE;
    else if ((line[index] == '\"' || line[index] == '\'') && (flag & PIPE) != 0)
        flag &= !QUOTE;
    while (1)
    {
        if (line[index] == '\0' || (line[index] == '|' && (flag & QUOTE) == 0))
        {
            if (line[index] == '|')
                line[index] = '\0';
            else
                flag &= !PIPE;
            new = new_cmd(&line[begin], flag, envp, begin);
            if (new == NULL)
                return ;
            if (begin == 0)
            {
                *cmds = new;
                tmp = *cmds;
            }
            else
            {
                (*cmds)->next = new;
                *cmds = (*cmds)->next;
            }
            if ((flag & PIPE) == 0)
                break ;
            begin = index + 1;
        }
        ++index;
    }
    *cmds = tmp;
}