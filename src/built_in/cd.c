/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:22:34 by soekim            #+#    #+#             */
/*   Updated: 2022/05/13 19:22:36 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/built_in.h"

void cd(t_cmd_info *cmd_info, int (*pipes)[2], int *input)
{
	int result;
	char *cwd_backup;

	cwd_backup = getcwd(0, 0);
	if (cmd_info->cmd_args[1][0] == '\0')
		result = chdir(getenv("HOME"));
	else if (cmd_info->cmd_args[1][0] == '~' \
			&& (cmd_info->cmd_args[1][1] == '\0' || cmd_info->cmd_args[1][1] == '/'))
	{
		result = chdir(getenv("HOME"));
		if (cmd_info->cmd_args[1][1] == '/')
		{
			cmd_info->cmd_args[1][0] = '.';
			result = chdir(cmd_info->cmd_args[1]);
			cmd_info->cmd_args[1][0] = '~';
		}
	}
	else
		result = chdir(cmd_info->cmd_args[1]);
	if (result == CD_FAILED)
	{
		chdir(cwd_backup);
		printf("cd: %s: No such file or directory\n", cmd_info->cmd_args[1]);
	}
	free(cwd_backup);
}
