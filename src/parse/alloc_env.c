/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnoh <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:59:26 by hnoh              #+#    #+#             */
/*   Updated: 2022/05/15 14:02:48 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parse.h"

void	alloc_env2(char *src, char **dest, char **envp, int *index)
{
	char	*key;
	char	*env_val;
	int		env_len;

	key = NULL;
	*index += get_env_key(src, &key);
	env_val = get_env_value(key, envp);
	env_len = ft_strlen(env_val);
	ft_memcpy(*dest, env_val, env_len);
	*dest += env_len;
	free(key);
}

int	alloc_env(char *src, char **dest, char **envp)
{
	char	*status;
	int		index;

	index = 0;
	if (src[1] == '?')
	{
		status = ft_itoa(g_exit_status);
		ft_memcpy(*dest, status, ft_strlen(status));
		*dest += ft_strlen(status);
		free(status);
		return (1);
	}
	else if (src[1] == '\0' || src[1] == '\"')
	{
		**dest = '$';
		*dest += 1;
		return (0);
	}
	alloc_env2(src, dest, envp, &index);
	return (index);
}
