#include "../include/minishell.h"

int check_whitespace(char *line)
{
    int len;
    int i;

    len = ft_strlen(line);
    i = -1;
    while (++i < len)
    {
        if (!((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
            return (0);
    }
    return (1);
}