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
	int	is_valid_arg;

	i = -1;
	is_valid_arg = TRUE;
	while (args[0] && args[0][++i])
	{
		if (ft_isdigit(args[0][i]) == FALSE)
		{
			printf("minishell: exit: %s: numeric argument required\n", args[0]);
			is_valid_arg = FALSE;
			break ;
		}
	}
	if (args[0] && is_valid_arg)
		g_exit_status = ft_atoi(args[0]);
	else
		g_exit_status = 0;
	if (args[0] && args[1] && is_valid_arg)
		printf("minishell: exit: too many arguments\n");
	exit(g_exit_status);
}
