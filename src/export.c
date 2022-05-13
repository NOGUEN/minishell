/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:54:58 by noguen            #+#    #+#             */
/*   Updated: 2022/05/12 19:54:59 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/export.h"

void    print_export(char **envp)
{
    int i;
    char    **sorted;
    char    *seperator;

    i = -1;
    sorted = sort_env(envp);
    while (sorted[++i])
    {
        seperator = ft_strchr(sorted[i], '=');
        if (seperator && *seperator == '=')
        {
            *seperator = '\0';
            printf("declare -x %s=\"%s\"\n", sorted[i], seperator+1);
            *seperator = '=';
        }
        else
            printf("declare -x %s\n", sorted[i]);
    }
    free_copied_env(sorted);
}

int	is_valid_key(char *key)
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
	return (TRUE);
}

int     is_valid_export(char *line)
{
    char    **str_arr;
    char    *key;
    int     i;
    int     ret;

    str_arr = ft_split(line, '=');
    key = str_arr[0];
    i = -1;
    ret = is_valid_key(key);
    while (str_arr[++i])
    {
        free(str_arr[i]);
    }
    free(str_arr);
    return (ret);
}

char    **find_existing_var(char *token, char **envp)
{
    char    *token_sep;
    char    *env_sep;
    
    token_sep = ft_strchr(token, '=');
    if (token_sep)
        *token_sep = '\0';
    while (*envp)
    {
        env_sep = ft_strchr(*envp, '=');
        if (env_sep)
            *env_sep = '\0';
        if (!ft_strcmp(token, *envp))
        {
            if (env_sep)
                *env_sep = '=';
            if (token_sep)
                *token_sep = '=';
            return envp;
        }
        if (env_sep)
            *env_sep = '=';
        ++envp;
    }
    if (token_sep)
        *token_sep = '=';
    return NULL;
}

void    export(t_cmd_info *cmd_info, char ***envp)
{
    int i;
    int count;
    char **target;
    char **new_env;

    if (!cmd_info->cmd_args[1])
    {
        print_export(*envp);
        return;
    }
    count = 0;
    i = 0;
    while (cmd_info->cmd_args[++i])
    {
        if (is_valid_export(cmd_info->cmd_args[i]))
        {
            target = find_existing_var(cmd_info->cmd_args[i], *envp);
            if (target) 
            {
                if (ft_strchr(cmd_info->cmd_args[i], '='))
                {
                    free(*target);
                    *target = ft_strdup(cmd_info->cmd_args[i]);
                }
            }
            else
                ++count;
        }
        else
            cmd_info->cmd_args[i][0] = '\0';
    }
    if (count == 0)
        return ;
    i = -1;
    while ((*envp)[++i])
        ++count;
    new_env = malloc((count+1)*sizeof(char *));
    new_env[count] = NULL;
    count = -1;
    i = -1;
    while ((*envp)[++i])
        new_env[++count] = (*envp)[i];
    i = 0;
    while (cmd_info->cmd_args[++i])
    {
        if (cmd_info->cmd_args[i][0])
            new_env[++count] = cmd_info->cmd_args[i];
    }
    free(*envp);
    *envp = new_env;
}