#include "../include/minishell.h"

char    *cut_string(char *str)
{
    char    *ret;
    char    *tmp;
    int     size;

    tmp = str;
    size = 0;
    while (tmp) {
        if (*tmp != ' ')
            size++;
        else
            break;
        tmp++;
    }
    ret = (char *)malloc(sizeof(char) * (size + 1));
    ft_strlcpy(ret, str, size + 1);
    return (ret);
}