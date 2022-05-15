/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:17:08 by noguen            #+#    #+#             */
/*   Updated: 2022/05/15 19:33:13 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_in.h"

char	**get_new_envp(char **envp, int new_size)
{
	int		env_i;
	int		new_i;
	char	**new;

	new = malloc((new_size + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	new[new_size] = NULL;
	new_i = 0;
	env_i = 0;
	while (new_i < new_size)
	{
		// printf("%s|\n",envp[ env_i]);
		if (envp[env_i][0])
		{
			new[new_i] = ft_strdup(envp[env_i]);
			++new_i;
		}
		else if (envp[env_i])
		{
			printf("%s\n", envp[env_i]);
			free(envp[env_i]);
		}

		++env_i;
	}
	
	return (new);
}

void	renew_envp(char ***envp, char **new_envp)
{
	char	**tmp;
	int		index;

	index = -1;
	tmp = *envp;
	while (tmp[++index])
		free(tmp[index]);
	free(*envp);
	*envp = new_envp;
}

void	unset(t_cmd_info *cmd_info, char ***envp)
{
	int		env_i;
	int		cmd_i;
	int		new_size;
	char	**new_envp;

	env_i = -1;
	new_size = 0;
	while ((*envp)[++env_i])
	{
		cmd_i = 0;
		while (cmd_info->cmd_args[++cmd_i])
		{
			if (!strcmp_bfdel((*envp)[env_i], cmd_info->cmd_args[cmd_i], '='))
			{
				printf("adasd %s\n",(*envp)[env_i]);
				(*envp)[env_i][0] = 0;
			}
		}
		if ((*envp)[env_i][0])
			++new_size;
	}
	printf("newsize %d\n",new_size);
	new_envp = get_new_envp(*envp, new_size);
	if (!new_envp)
		g_exit_status = 1;
	else
		renew_envp(envp, new_envp);
}
