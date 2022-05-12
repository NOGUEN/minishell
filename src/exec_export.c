#include "../includes/minishell.h"

int cnt_envp(char **envp)
{
    int i;

    i = 0;
    if (envp != NULL)
    {
        while (envp[i])
            ++i;
    }
    return (i);
}

void    print_env_value(char *str, int fd)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (str[i] == '=')
            break ;
    }
    while (str[++i])
    {
        write(fd, str, i);
        write(fd, "\"", 1);
        write(fd, str + i, ft_strlen(str + i));
        write(fd, "\"", 1);
    }
}

int check_key(char *cmd, char **envp)
{
    int i;
    int key_index;

    i = -1;
    key_index = 0;
    while(cmd[key_index] != '=')
        ++key_index;
    while (envp[++i])
    {
        if (ft_strncmp(envp[i], cmd, key_index) == 0)
            return (i);
    }
    return (-1);
}

void    add_envp(char *new_envp, char ***envp)
{
    char    **new;
    int     i;
    int     row;

    i = -1;
    row = cnt_envp(*envp);
    new = (char **)malloc(sizeof(char *) * (row + 1));
    if (new == NULL)
        return ;
    while ((*envp)[++i])
    {
        new[i] = ft_strdup(*(envp)[i]);
        free(*envp[i]);
    }
    free(*envp);
    new[i] = ft_strdup(new_envp);
    *envp = new;
}

void    print_export(char **envp, int fd)
{
    int i;
    char    **sorted;

    i = -1;
    sorted = sort_envp(envp);
    while (sorted[++i])
    {
        print_str_fd("declare -x ", fd);

    }
}

int     check_valid_export(char *line)
{
    char    **str_arr;
    char    *key;
    int     i;
    int     ret;

    key = str_arr[0];
    str_arr = ft_split(line, '=');
    i = -1;
    ret = ft_valid_key(key);
    while (str_arr[++i])
    {
        free(str_arr[i]);
    }
    free(str_arr);
    return (ret);
}

void    exec_export(t_cmd *cmds, char ***envp, int fd)
{
    int i;
    int key_index;

    i = 1;
    while (cmds->cmdline[i].cmd && cmds->cmdline[i].redir_flag == 0)
    {
        if (check_valid_export(cmds->cmdline[i].cmd))
        {
            
        }
    }
}