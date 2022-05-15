/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:22:34 by soekim            #+#    #+#             */
/*   Updated: 2022/05/14 17:11:55 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_in.h"

int	cd_from_home(t_cmd_info *cmd_info)
{
	int		result;

	result = chdir(getenv("HOME"));
	if (cmd_info->cmd_args[1][1] == '/')
	{
		cmd_info->cmd_args[1][0] = '.';
		result = chdir(cmd_info->cmd_args[1]);
		cmd_info->cmd_args[1][0] = '~';
	}
	return (result);
}

void	cd(t_cmd_info *cmd_info)
{
	int		result;
	char	*cwd_backup;

	cwd_backup = getcwd(0, 0);
	if (cmd_info->cmd_args[1] == NULL || cmd_info->cmd_args[1][0] == '\0')
		result = chdir(getenv("HOME"));
	else if (cmd_info->cmd_args[1][0] == '~' \
			&& (cmd_info->cmd_args[1][1] == '\0'
				|| cmd_info->cmd_args[1][1] == '/'))
		result = cd_from_home(cmd_info);
	else
		result = chdir(cmd_info->cmd_args[1]);
	if (result == CD_FAILED)
	{
		g_exit_status = 1;
		chdir(cwd_backup);
		printf("cd: %s: No such file or directory\n", cmd_info->cmd_args[1]);
	}
	free(cwd_backup);
}
