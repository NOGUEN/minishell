/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:55:21 by noguen            #+#    #+#             */
/*   Updated: 2022/05/12 18:55:22 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *cut_string(char **str)
{
    char    *ret;
    char    *tmp;
    int     size;
    int     i;

    ret = NULL;
    size = 0;
    tmp = *str;
    while (tmp) {
        if (*tmp == ' ')
            break ;
        else if (*tmp == '\"' || *tmp == '\'')
            break ;
        else
            ++size;
        ++(tmp);
    }
    ret = (char *)malloc(sizeof(char) * (size + 1));
    ft_strlcpy(ret, *str, size + 1);
    i = -1;
    while (++i < size)
        ++(*str);
    return (ret);
}

char    **copy_envp(char **envp)
{
    char    **new;
    int     i;

    i = -1;
    while (envp[++i])
        i++;
    new = malloc(sizeof(char *) * (i + 1));
    if (new == NULL)
        return (NULL);
    i = -1;
    while (envp[++i])
        new[i] = ft_strdup(envp[i]);
    new[i] = NULL;
    return (new);
}

char    **sort_env(char **envp)
{
    int     i;
    int     j;
    char    **new;
    char    *tmp;

    i = -1;
    j = 0;
    new = copy_envp(envp);
    while (new[++i])
    {
        j = i;
        while (new[++j])
        {
            if (ft_strncmp(new[i], new[j], ft_strlen(new[i])) > 0)
            {
                tmp = new[i];
                new[i] = new[j];
                new[j] = tmp;
            }
        }
    }
    return (new);
}

void    print_str_fd(char *s, int fd)
{
    if (fd < 0 || !(s))
        return ;
    write(fd, s, ft_strlen(s));
}
