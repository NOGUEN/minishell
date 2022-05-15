/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noguen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 13:16:58 by noguen            #+#    #+#             */
/*   Updated: 2022/05/14 13:17:03 by noguen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_in.h"

void	ft_exit(char **args)
{
	int	i;

	i = -1;
	while (args[0] && args[0][++i])
	{
		if (ft_isdigit(args[0][i]) == FALSE)
		{
			printf("minishell: exit: %s: numeric argument required\n", args[0]);
			g_exit_status = 255;
			exit(g_exit_status);
		}
	}
	if (args[0] && args[1])
	{
		printf("minishell: exit: too many arguments\n");
		g_exit_status = 1;
		return ;
	}
	if (args[0])
		g_exit_status = ft_atoi(args[0]);
	else
		g_exit_status = 0;
	exit(g_exit_status);
}
