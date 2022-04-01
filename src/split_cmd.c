#include "../include/minishell.h"

t_token *cmd_split(char const *s)
{
    int     i;
    int     cursor;
    t_token *result;

    result = malloc(sizeof(t_token) * (split_count(s) + 1));
    if (result == NULL)
        return (NULL);
    while (*s)
    {
        
    }
}