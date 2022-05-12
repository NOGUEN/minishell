/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:55:53 by noguen            #+#    #+#             */
/*   Updated: 2022/05/12 19:55:54 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *get_env_value(char *key, char **envp)
{
    int i;

    i = -1;
    while (envp[++i])
    {
        if (!ft_strncmp(key, envp[i], ft_strlen(key)) 
                && envp[i][ft_strlen(key)] == '=')
            return (envp[i] + ft_strlen(key) + 1);
    }
    return (NULL);
}

int get_env_key(char *src, char **key)
{
    int     key_len;

    src++;
    *key = cut_string(&src);
    key_len = ft_strlen(*key) + 1;
    return (key_len);
}
