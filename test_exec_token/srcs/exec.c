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

void init_fork_pipes(int (*pipes)[2])
{
	if (pipe(pipes[PTOC]) < 0)
		error_exit("Error : pipe");
	if (pipe(pipes[CTOP]) < 0)
		error_exit("Error : pipe");
	return;
}

void transfer_data(int fd_src, int *fd_targets)
{
	int read_result;
	int *fd_target;
	char buf[33];

	buf[32] = 0;
	read_result = 1;
	while (TRUE)
	{
		read_result = read(fd_src, buf, 32);
		if (read_result<=0)
			break;
		buf[read_result] = 0;
		fd_target = fd_targets;
		while (*fd_target != END_OF_FDS)
		{
			ft_putstr_fd(buf, *fd_target);
			++fd_target;
		}
	}
	return;
}

void new_exec(t_cmd *cmd_list, char **envp)
{
	t_cmd_info cmd_info;
	int pipes[2][2];
	// int fds_to_write[3];
	int input;

	input = STDIN;
	while (cmd_list)
	{
		init_fork_pipes(pipes);
		init_cmd_info(&cmd_info, cmd_list->cmdline,pipes);
		if (cmd_info.in_fd==NO_DATA)
			cmd_info.in_fd = input;
		if (cmd_info.out_fd==NO_DATA)
		{
			if (cmd_list->next)
				cmd_info.out_fd = pipes[CTOP][WR];
			else
				cmd_info.out_fd = STDOUT;
		}

		// when input exist in token, input of pipe doesn't work
		// when output exist in token, should write both output of pipe and output redirection file
		exec_cmd(&cmd_info, envp, pipes);

		if (input != STDIN)
			close(input);

		if (cmd_info.out_name)
		{
			close(pipes[CTOP][RD]);
			input = open(cmd_info.out_name, O_RDONLY);
		}
		else
			input = pipes[CTOP][RD];
		
		free(cmd_info.cmd_arg);
		cmd_list = cmd_list->next;
	}
}

void exec_cmd(t_cmd_info *cmd_info, char **envp, int (*pipes)[2])
{
	int pid;
	char *path;

	pid = fork();
	if (pid < 0)
		error_exit("Error : fork");
	
	if (pid == CHILD)
	{
		close(pipes[PTOC][WR]);
		close(pipes[CTOP][RD]);
		path = find_cmdpath(cmd_info->cmd_arg[0], envp);
		dup2(cmd_info->in_fd, STDIN);
		dup2(cmd_info->out_fd, STDOUT);
		execve(path, cmd_info->cmd_arg, envp);
		exit(0);
	}
	else
	{
		close(pipes[PTOC][RD]);
		close(pipes[PTOC][WR]);
		close(pipes[CTOP][WR]);
		waitpid(CHILD,NULL,0);
	}
	return;
}