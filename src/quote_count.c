#include "../include/minishell.h"

char *find_env(char *str, char **envp)
{
    int len;
    char **tmp;

    len = ft_strlen(str);
    tmp = envp;
    while (*tmp)
    {
        if (ft_strncmp(str, *tmp, len) == 0)
            return *tmp;
        tmp++;
    }
    return (NULL);
}

int env_len(char *str, char **envp)
{
    int len;
    char *env;

    len = 0;
    env = find_env(str, envp);
    if (env != NULL)
        len = ft_strlen(env) - ft_strlen(str) - 1;
    return (len);
}

int dquote_cnt(char **cmd, char **envp)
{
    int size;
    char *tmp;

    size = 0;
    printf("%s\n", envp[0]);
    (*cmd)++;
    while (**cmd && **cmd != '\"')
    {
        if (**cmd == '$')
        {
            ++(*cmd);
            tmp = cut_string(cmd);
            printf("%s\n", tmp);
            size += env_len(tmp, envp);
            free(tmp);
        }
        else
            size++;
        (*cmd)++;
    }
    printf("dquote : %d\n", size);
    return (size);
}

int squote_cnt(char **cmd)
{
    int size;

    size = 0;
    (*cmd)++;
    while (**cmd && **cmd != '\'')
    {
        ++size;
        ++(*cmd);
    }
    return (size);
}