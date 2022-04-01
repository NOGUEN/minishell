/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:56:55 by soekim            #+#    #+#             */
/*   Updated: 2022/04/01 12:20:14 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

void	init_pipe(int (*pipes)[2])
{
	if (pipe(pipes[PTOC]) < 0)
		error_exit("Error : pipe");
	if (pipe(pipes[CTOP]) < 0)
		error_exit("Error : pipe");
	return ;
}

void	exec_arg(t_arg *arg, char **envp, t_inout *inout)
{
	int		i;
	int		input;
	int		cmd_num;
	int		pipes[2][2];

	if (arg->cnt == 3 || arg->cnt == 4)
		cmd_num = arg->cnt - 2;
	else if (arg->cnt >= 5)
		cmd_num = arg->cnt - 3;
	else
		return ;
	input = inout->in.fd;
	i = 0;
	arg->vec += 2;
	while (i < cmd_num)
	{
		init_pipe(pipes);
		transfer_data(input, pipes[PTOC][WR]);
		exec_cmd(arg->vec[i], envp, pipes);
		close(input);
		input = pipes[CTOP][RD];
		close(pipes[PTOC][WR]);
		++i;
	}
	transfer_data(input, inout->out.fd);
}

void	exec_cmd(char *cmd, char **envp, int (*pipes)[2])
{
	int		pid;
	char	*path;
	char	**cmd_arg;

	pid = fork();
	if (pid < 0)
		error_exit("Error : fork");
	if (pid != CHILD)
	{
		close(pipes[PTOC][RD]);
		close(pipes[CTOP][WR]);
	}
	if (pid == CHILD)
	{
		close(pipes[PTOC][WR]);
		close(pipes[CTOP][RD]);
		path = find_cmdpath(cmd, envp);
		cmd_arg = ft_split(cmd, ' ');
		dup2(pipes[PTOC][RD], STDIN);
		dup2(pipes[CTOP][WR], STDOUT);
		execve(path, cmd_arg, envp);
		exit(0);
	}
	return ;
}
