/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 22:56:55 by soekim            #+#    #+#             */
/*   Updated: 2022/05/14 17:18:25 by hnoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	exec(t_cmd *cmd_list, char ***envp)
{
	t_cmd_info	cmd_info;
	int			pipes[2][2];
	int			input;

	input = STDIN;
	while (cmd_list)
	{
		g_exit_status = 0;
		init_fork_pipes(pipes);
		init_cmd_info(&cmd_info, cmd_list->tokens, pipes);
		if (g_exit_status)
			return (close_fds(&cmd_info, pipes, &input));
		handle_pipe_inout(cmd_list, &cmd_info, pipes, input);
		if (executed_built_in(&cmd_info, envp) || g_exit_status)
			close_fds(&cmd_info, pipes, &input);
		else
		{
			fork_and_exec(&cmd_info, *envp, pipes);
			if (input != STDIN)
				close(input);
			input = pipes[C_TO_P][RD];
		}
		free(cmd_info.cmd_args);
		cmd_list = cmd_list->next;
	}
}

void	handle_pipe_inout(t_cmd *cmd_list, t_cmd_info *cmd_info, \
							int (*pipes)[2], int input)
{
	if (cmd_info->in_fd == NO_DATA)
		cmd_info->in_fd = input;
	if (cmd_info->out_fd == NO_DATA)
	{
		if (cmd_list->next)
			cmd_info->out_fd = pipes[C_TO_P][WR];
		else if (cmd_info->out_fd == NO_DATA)
			cmd_info->out_fd = STDOUT;
	}
}

int	executed_built_in(t_cmd_info *cmd_info, char ***envp)
{
	if (!ft_strcmp(cmd_info->cmd_args[0], "exit"))
		ft_exit(&cmd_info->cmd_args[1]);
	else if (!ft_strcmp(cmd_info->cmd_args[0], "cd"))
		cd(cmd_info);
	else if (!ft_strcmp(cmd_info->cmd_args[0], "unset"))
		unset(cmd_info, envp);
	else if (!ft_strcmp(cmd_info->cmd_args[0], "export")
		&& cmd_info->cmd_args[1])
		export_new(cmd_info, envp);
	else
		return (FALSE);
	return (TRUE);
}

void	fork_and_exec(t_cmd_info *cmd_info, char **envp, int (*pipes)[2])
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error_exit("Error : fork");
	if (pid == CHILD)
		exec_cmd(cmd_info, envp, pipes);
	else
	{
		close(pipes[P_TO_C][RD]);
		close(pipes[P_TO_C][WR]);
		close(pipes[C_TO_P][WR]);
		waitpid(CHILD, &g_exit_status, 0);
		g_exit_status >>= 8;
	}
	return ;
}

void	exec_cmd(t_cmd_info *cmd_info, char **envp, int (*pipes)[2])
{
	char	*path;

	close(pipes[P_TO_C][WR]);
	close(pipes[C_TO_P][RD]);
	if (ft_strcmp("env", cmd_info->cmd_args[0])
		&& ft_strcmp("export", cmd_info->cmd_args[0]))
		path = find_cmdpath(cmd_info->cmd_args[0], envp);
	dup2(cmd_info->in_fd, STDIN);
	dup2(cmd_info->out_fd, STDOUT);
	if (!ft_strcmp("env", cmd_info->cmd_args[0]))
		env(envp);
	else if (!ft_strcmp("export", cmd_info->cmd_args[0]))
		print_export(envp);
	else
		execve(path, cmd_info->cmd_args, envp);
	exit(0);
}
