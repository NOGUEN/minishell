/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:12:16 by soekim            #+#    #+#             */
/*   Updated: 2022/04/01 12:19:31 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/utils.h"

int	strdelcmp(char *s1, char *s2, int del)
{
	while (*s1 && *s2 && *s1 != del && *s2 != del)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		++s1;
		++s2;
	}
	if (*s1 == del || *s2 == del)
		return (0);
	else
		return (*s1 - *s2);
}

void	error_exit(char *str)
{
	ft_putendl_fd(str, STDOUT);
	exit(1);
}

int	open_file(char *name, int mode)
{
	int		fd;

	if (!name || name[0] == '\0')
	{
		printf("syntax error near unexpected token `newline'\n");
		fd = ERR_IN_OUT;
		g_exit_status = 258;
	}
	else
		fd = open(name, mode, S_IWUSR|S_IRUSR);
	return (fd);
}

void	close_fds(t_cmd_info *cmd_info, int (*pipes)[2], int *input)
{
	close(pipes[P_TO_C][WR]);
	close(pipes[P_TO_C][RD]);
	close(pipes[C_TO_P][RD]);
	if (pipes[C_TO_P][WR] != cmd_info->out_fd)
		close(pipes[C_TO_P][WR]);
	if (*input != STDIN)
	{
		close(*input);
		*input = STDIN;
	}
	if (cmd_info->out_fd != NO_DATA && cmd_info->out_fd != STDOUT)
		close(cmd_info->out_fd);
}