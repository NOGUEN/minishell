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
	if (pipe(pipes[P_TO_C]) < 0)
		error_exit("Error : pipe");
	if (pipe(pipes[C_TO_P]) < 0)
		error_exit("Error : pipe");
	return;
}

#define CD_FAILED -1

void cd_and_close_fds(t_cmd_info *cmd_info, int (*pipes)[2], int input)
{
	int result;
	char *cwd_backup;

	cwd_backup = getcwd(0, 0);
	if (cmd_info->cmd_args[1][0] == '\0')
		result = chdir(getenv("HOME"));
	else if (cmd_info->cmd_args[1][0] == '~'
			&&(cmd_info->cmd_args[1][1] == '\0' 
				|| cmd_info->cmd_args[1][1] == '/'))
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
	close(pipes[P_TO_C][WR]);
	close(pipes[P_TO_C][RD]);
	close(pipes[C_TO_P][RD]);
	if (pipes[C_TO_P][WR]!= cmd_info->out_fd)
		close(pipes[C_TO_P][WR]);
	if (input != STDIN)
		close(input);
	if (cmd_info->out_fd != NO_DATA &&cmd_info->out_fd != STDOUT)
		close(cmd_info->out_fd);
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
				cmd_info.out_fd = pipes[C_TO_P][WR];
			else
				cmd_info.out_fd = STDOUT;
		}

		// when input exist in token, input of pipe doesn't work
		// when output exist in token, should write both output of pipe and output redirection file
		if (!ft_strcmp(cmd_info.cmd_args[0],"cd"))
		{
			cd_and_close_fds(&cmd_info, pipes, input);
			cmd_list = cmd_list->next;
			continue;
		}

		exec_cmd(&cmd_info, envp, pipes);
		

		if (input != STDIN)
			close(input);
		// if (cmd_info.out_name)
		// {
		// 	close(pipes[C_TO_P][RD]);
		// 	input = open(cmd_info.out_name, O_RDONLY);
		// }
		// else
		// when meet redir output bash acts like no pipes before
			input = pipes[C_TO_P][RD];
		
		free(cmd_info.cmd_args);
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
		close(pipes[P_TO_C][WR]);
		close(pipes[C_TO_P][RD]);
		if (!ft_strcmp( cmd_info->cmd_args[0],"exit"))
			exit(0);// should refactor consider signal handling when exit cmd
		path = find_cmdpath(cmd_info->cmd_args[0], envp);
		dup2(cmd_info->in_fd, STDIN);
		dup2(cmd_info->out_fd, STDOUT);
		execve(path, cmd_info->cmd_args, envp);
		exit(0);
	}
	else
	{
		close(pipes[P_TO_C][RD]);
		close(pipes[P_TO_C][WR]);
		close(pipes[C_TO_P][WR]);
		waitpid(CHILD,NULL,0);
	}
	return;
}