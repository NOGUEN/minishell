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

#include "../../include/built_in.h"

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

void    export_new(t_cmd_info *cmd_info, char ***envp)
{
    int i;
    int count;
    char **new_env;

    update_existing_count_new(cmd_info, envp, &count);
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

void    update_existing_count_new(t_cmd_info *cmd_info, char ***envp, int *pcount)
{
    int     i;
    int     count;
    char    **existing;
    
    count = 0;
    i = 0;
    while (cmd_info->cmd_args[++i])
    {
        if (is_valid_export(cmd_info->cmd_args[i]))
        {
            existing = find_existing_var(cmd_info->cmd_args[i], *envp);
            if (existing) 
                update_existing(existing, cmd_info->cmd_args[i]);
            else
                ++count;
        }
        else
            cmd_info->cmd_args[i][0] = '\0';
    }
    i = -1;
    *pcount = count;
}

void    update_existing(char **existing, char *new_val)
{
    if (ft_strchr(new_val, '='))
    {
        free(*existing);
        *existing = ft_strdup(new_val);
    }
}