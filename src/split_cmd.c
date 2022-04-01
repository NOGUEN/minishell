#include "../include/minishell.h"

t_token *cmd_split(char const *s, char c)
{
    int     i;
    int     cursor;
    t_token *result;

    if (s == NULL)
        return (NULL);
}