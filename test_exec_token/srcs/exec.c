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

void init_pipe(int (*pipes)[2])
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
		if (read_result<0)
			break;
		// printf("%s %d\n",buf, read_result);
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

void exec_arg(t_cmd_list *cmd_list, char **envp)
{
	t_token_info token_info;
	int pipes[2][2];
	int fds_to_write[3];
	int last_pipe;
	int last_outredir;

	fds_to_write[0] = fds_to_write[1] = fds_to_write[2] = END_OF_FDS;
	last_pipe = 0;
	last_outredir = NO_DATA;
	while (cmd_list)
	{
		init_pipe(pipes);
		init_token_info(&token_info, cmd_list->tokens);

		// printf("to info in %d out %d \ncmd\n",token_info.input, token_info.output);
		// for (char ** cmd = token_info.cmd_arg; *cmd;++cmd) printf("%s\t",*cmd);
		// printf("\n");

		// consider how to get input from stdin when << token
		// when input exist in token, input of pipe doesn't work
		// when output exist in token, should write both output of pipe and output redirection file
		if (token_info.input == NO_DATA)
		{
			fds_to_write[0] = pipes[PTOC][WR];
			if (last_outredir==NO_DATA)
				fds_to_write[1] = END_OF_FDS;
			else
				fds_to_write[1] = last_outredir;
			transfer_data(last_pipe, fds_to_write);
			close(last_outredir);
		}
		else
		{
			if (last_outredir==NO_DATA)
				fds_to_write[0] = END_OF_FDS;
			else
				fds_to_write[0] = last_outredir;
			fds_to_write[1] = END_OF_FDS;
			transfer_data(last_pipe, fds_to_write);
			fds_to_write[0] = pipes[PTOC][WR];
			transfer_data(token_info.input, fds_to_write);
		}
		if (last_pipe)
			close(last_pipe);

		exec_cmd(&token_info, envp, pipes);
		last_pipe = pipes[CTOP][RD];
		last_outredir = token_info.output;
		close(pipes[PTOC][WR]);
		// free token_info
		cmd_list = cmd_list->next;
	}

	fds_to_write[1] = END_OF_FDS;
	if (last_outredir == NO_DATA)
		fds_to_write[0] = STDOUT;
	else
		fds_to_write[0] = last_outredir;
	transfer_data(last_pipe, fds_to_write);
	if (last_outredir != NO_DATA)
		close(last_outredir);
	if (last_pipe)
		close(last_pipe);
}

void exec_cmd(t_token_info *token_info, char **envp, int (*pipes)[2])
{
	int pid;
	char *path;

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
		path = find_cmdpath(token_info->cmd_arg[0], envp);
		dup2(pipes[PTOC][RD], STDIN);
		dup2(pipes[CTOP][WR], STDOUT);
		execve(path, token_info->cmd_arg, envp);
		exit(0);
	}
	return;
}
