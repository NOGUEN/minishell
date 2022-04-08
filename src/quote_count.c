#include "../include/minishell.h"

int env_value_size(char *str, int size, char **envp)
{
    int index;

    index = -1;
    while (envp[++index])
    {
        if ((ft_strncmp(&str[1], envp[index], size))
                && envp[index][size] == '=')
            return (ft_strlen(envp[index] + size + 1));
    }
    return (0);
}

int env_key_size(char *str)
{
    int index;

    index = 0;
    if (ft_isdigit(str[1]))
        return (1);
    while (str[++index])
    {
        if (!(ft_isalnum(str[index]) || str[index]))
    }
}

int env_len(char *str, int size, char **envp)
{
    
}


int dquote_cnt(char **cmd, char **envp)
{
    int size;

    size = 0;
    while (*(*cmd++) && **cmd != '\"')
    {
        if (**cmd == '$')
            size += env_cnt();
        else
            size++;
    }
    return (size);
}

int squote_cnt(char **cmd)
{
    int size;

    size = 0;
    (*cmd)++;
    while (*(*cmd++) && **cmd != '\'')
    {
        ++size;
        ++cmd;
    }
    return (size);
}