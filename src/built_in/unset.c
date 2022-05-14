/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:17:08 by noguen            #+#    #+#             */
/*   Updated: 2022/05/14 15:19:20 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_in.h"

void	unset(t_cmd_info *cmd_info, char ***envp)
{
	int		i;
	int		j;
	int		count;
	char	**new;

	i = -1;
	count = 0;
	while ((*envp)[++i])
	{
		j = 0;
		while (cmd_info->cmd_args[++j])
		{
			if (!strdelcmp((*envp)[i], cmd_info->cmd_args[j], '='))
				(*envp)[i][0] = 0;
		}
		if ((*envp)[i][0])
			++count;
	}
	new = malloc((count + 1) * sizeof(char *));
	new[count] = NULL;
	j = count;
	while (--i >= 0)
	{
		if ((*envp)[i][0])
			new[--j] = (*envp)[i];
	}
	free(*envp);
	*envp = new;
}
