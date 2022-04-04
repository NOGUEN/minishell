#include "../include/minishell.h"

int check_whitespace(char *line)
{
    int len;
    int i;

    len = ft_strlen(line);
    i = -1;
    while (++i < len)
    {
        if (!ft_isspace((int)line[i]))
            return (0);
    }
    return (1);
}