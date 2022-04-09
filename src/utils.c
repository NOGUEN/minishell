#include "../include/minishell.h"

char    *cut_string(char **str)
{
    char    *ret;
    char    *tmp;
    int     size;
    int     i;

    size = 0;
    tmp = *str;
    while (tmp) {
        if (*tmp == ' ')
            break ;
        else if (*tmp == '\"' || *tmp == '\'')
            break ;
        else
            ++size;
        ++(*tmp);
    }
    ret = (char *)malloc(sizeof(char) * (size + 1));
    ft_strlcpy(ret, *str, size + 1);
    i = -1;
    while (++i < size)
        ++(*str);
    return (ret);
}