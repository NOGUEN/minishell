#include "../include/export.h"

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

void    print_export(char **envp)
{
    int i;
    char    **sorted;

    i = -1;
    sorted = sort_env(envp);
    while (sorted[++i])
        printf("declare -x %s", sorted[i]);
}

int	ft_valid_key(char *key)
{
	int i;

	i = 0;
	if (ft_strlen(key) == 0)
		return (0);
	while (key[i])
	{
		if (ft_isdigit(key[0]))
			return (0);
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int     check_valid_export(char *line)
{
    char    **str_arr;
    char    *key;
    int     i;
    int     ret;

    str_arr = ft_split(line, '=');
    key = str_arr[0];
    i = -1;
    ret = ft_valid_key(key);
    while (str_arr[++i])
    {
        free(str_arr[i]);
    }
    free(str_arr);
    return (ret);
}

void    export(t_cmd *cmds, char ***envp)
{
    int i;
    int count;
    int key_index;
    char **new_env;

    if (!cmds->tokens[1].cmd)
    {
        print_export(*envp);
        return;
    }
    i = -1;
    count = 0;
    while ((*envp)[++i])
        ++count;
    i = 0;
    while (cmds->tokens[++i].cmd)
    {
        if (check_valid_export(cmds->tokens[i].cmd))
        {
            cmds->tokens[i].cmd[0] = '\0';
            ++count;
        }
    }
    new_env = malloc((count+1)*sizeof(char *));
    new_env[count] = NULL;
    count = -1;
    i = -1;
    while ((*envp)[++i])
        new_env[++count] = (*envp)[i];
    i = 0;
    while (cmds->tokens[++i].cmd)
    {
        if (cmds->tokens[i].cmd[0])
            new_env[++count] = cmds->tokens[i].cmd;
    }
    free(*envp);
    *envp = new_env;
}