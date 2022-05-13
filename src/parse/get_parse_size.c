/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parse_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:55:45 by noguen            #+#    #+#             */
/*   Updated: 2022/05/12 18:55:46 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

int get_parse_size(char *cmd, char **envp)
{
    int size;
    char *tmp;

    size = 0;
    while (*cmd)
    {
        if (*cmd == '\'')
        {
            size += squote_cnt(&cmd);
            break ;
        }
        else if (*cmd == '\"')
        {
            size += dquote_cnt(&cmd, envp);
            break ;
        }
        else if (*cmd == '$')
        {
            ++cmd;
            tmp = cut_string(&cmd);
            size += env_len(tmp, envp);
            break ;
        }
        ++cmd;
    }
    return (size);
}
